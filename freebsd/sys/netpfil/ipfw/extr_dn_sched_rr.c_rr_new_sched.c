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
struct rr_si {int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;
struct dn_sch_inst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND (char*) ; 

__attribute__((used)) static int
rr_new_sched(struct dn_sch_inst *_si)
{
	struct rr_si *si = (struct rr_si *)(_si + 1);

	ND("called");
	si->head = si->tail = NULL;

	return 0;
}