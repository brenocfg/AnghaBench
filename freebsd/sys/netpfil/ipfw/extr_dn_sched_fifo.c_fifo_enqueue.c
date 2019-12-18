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
struct mbuf {int dummy; } ;
struct dn_sch_inst {int dummy; } ;
struct dn_queue {int dummy; } ;

/* Variables and functions */
 int dn_enqueue (struct dn_queue*,struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
fifo_enqueue(struct dn_sch_inst *si, struct dn_queue *q, struct mbuf *m)
{
	/* XXX if called with q != NULL and m=NULL, this is a
	 * re-enqueue from an existing scheduler, which we should
	 * handle.
	 */
	(void)q;
	return dn_enqueue((struct dn_queue *)(si+1), m, 0);
}