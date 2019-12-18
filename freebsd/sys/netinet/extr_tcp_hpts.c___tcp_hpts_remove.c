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
struct inpcb {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int HPTS_REMOVE_INPUT ; 
 int HPTS_REMOVE_OUTPUT ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct tcp_hpts_entry* tcp_hpts_lock (struct inpcb*) ; 
 int /*<<< orphan*/  tcp_hpts_remove_locked_input (struct tcp_hpts_entry*,struct inpcb*,int,int) ; 
 int /*<<< orphan*/  tcp_hpts_remove_locked_output (struct tcp_hpts_entry*,struct inpcb*,int,int) ; 
 struct tcp_hpts_entry* tcp_input_lock (struct inpcb*) ; 

void
__tcp_hpts_remove(struct inpcb *inp, int32_t flags, int32_t line)
{
	struct tcp_hpts_entry *hpts;

	INP_WLOCK_ASSERT(inp);
	if (flags & HPTS_REMOVE_OUTPUT) {
		hpts = tcp_hpts_lock(inp);
		tcp_hpts_remove_locked_output(hpts, inp, flags, line);
		mtx_unlock(&hpts->p_mtx);
	}
	if (flags & HPTS_REMOVE_INPUT) {
		hpts = tcp_input_lock(inp);
		tcp_hpts_remove_locked_input(hpts, inp, flags, line);
		mtx_unlock(&hpts->p_mtx);
	}
}