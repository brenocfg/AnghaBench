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
typedef  int /*<<< orphan*/  uint32_t ;
struct timeval {int dummy; } ;
struct tcp_hpts_entry {int /*<<< orphan*/  p_mtx; int /*<<< orphan*/  p_nxt_slot; } ;
struct inpcb {int dummy; } ;
struct hpts_diag {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_hpts_insert_locked (struct tcp_hpts_entry*,struct inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hpts_diag*,struct timeval*) ; 
 struct tcp_hpts_entry* tcp_hpts_lock (struct inpcb*) ; 

uint32_t
tcp_hpts_insert_diag(struct inpcb *inp, uint32_t slot, int32_t line, struct hpts_diag *diag)
{
	struct tcp_hpts_entry *hpts;
	uint32_t slot_on;
	struct timeval tv;

	/*
	 * We now return the next-slot the hpts will be on, beyond its
	 * current run (if up) or where it was when it stopped if it is
	 * sleeping.
	 */
	INP_WLOCK_ASSERT(inp);
	hpts = tcp_hpts_lock(inp);
	microuptime(&tv);
	tcp_hpts_insert_locked(hpts, inp, slot, line, diag, &tv);
	slot_on = hpts->p_nxt_slot;
	mtx_unlock(&hpts->p_mtx);
	return (slot_on);
}