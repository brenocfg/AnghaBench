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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __tcp_queue_to_input_locked (struct inpcb*,struct tcp_hpts_entry*,int) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct tcp_hpts_entry* tcp_input_lock (struct inpcb*) ; 

int32_t
__tcp_queue_to_input(struct inpcb *inp, int line)
{
	struct tcp_hpts_entry *hpts;
	int32_t ret;

	hpts = tcp_input_lock(inp);
	ret = __tcp_queue_to_input_locked(inp, hpts, line);
	mtx_unlock(&hpts->p_mtx);
	return (ret);
}