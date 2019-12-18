#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcp_hpts_entry {int /*<<< orphan*/  p_mtx; } ;
struct inpcb {scalar_t__ inp_in_hpts; int inp_hpts_cpu_set; int inp_input_cpu_set; scalar_t__ inp_in_input; void* inp_input_cpu; void* inp_hpts_cpu; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 void* hpts_cpuid (struct inpcb*) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct tcp_hpts_entry* tcp_hpts_lock (struct inpcb*) ; 
 struct tcp_hpts_entry* tcp_input_lock (struct inpcb*) ; 

void
__tcp_set_hpts(struct inpcb *inp, int32_t line)
{
	struct tcp_hpts_entry *hpts;

	INP_WLOCK_ASSERT(inp);
	hpts = tcp_hpts_lock(inp);
	if ((inp->inp_in_hpts == 0) &&
	    (inp->inp_hpts_cpu_set == 0)) {
		inp->inp_hpts_cpu = hpts_cpuid(inp);
		inp->inp_hpts_cpu_set = 1;
	}
	mtx_unlock(&hpts->p_mtx);
	hpts = tcp_input_lock(inp);
	if ((inp->inp_input_cpu_set == 0) &&
	    (inp->inp_in_input == 0)) {
		inp->inp_input_cpu = hpts_cpuid(inp);
		inp->inp_input_cpu_set = 1;
	}
	mtx_unlock(&hpts->p_mtx);
}