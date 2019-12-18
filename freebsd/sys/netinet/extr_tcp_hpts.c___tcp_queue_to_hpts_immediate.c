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
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct tcp_hpts_entry* tcp_hpts_lock (struct inpcb*) ; 
 int tcp_queue_to_hpts_immediate_locked (struct inpcb*,struct tcp_hpts_entry*,int,int /*<<< orphan*/ ) ; 

int
__tcp_queue_to_hpts_immediate(struct inpcb *inp, int32_t line)
{
	int32_t ret;
	struct tcp_hpts_entry *hpts;

	INP_WLOCK_ASSERT(inp);
	hpts = tcp_hpts_lock(inp);
	ret = tcp_queue_to_hpts_immediate_locked(inp, hpts, line, 0);
	mtx_unlock(&hpts->p_mtx);
	return (ret);
}