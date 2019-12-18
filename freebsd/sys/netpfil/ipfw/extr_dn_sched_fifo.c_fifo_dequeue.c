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
 struct mbuf* dn_dequeue (struct dn_queue*) ; 

__attribute__((used)) static struct mbuf *
fifo_dequeue(struct dn_sch_inst *si)
{
	return dn_dequeue((struct dn_queue *)(si + 1));
}