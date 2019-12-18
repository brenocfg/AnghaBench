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
struct prio_si {scalar_t__ bitmap; int /*<<< orphan*/  q_array; } ;
struct dn_sch_inst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
prio_new_sched(struct dn_sch_inst *_si)
{
	struct prio_si *si = (struct prio_si *)(_si + 1);

	bzero(si->q_array, sizeof(si->q_array));
	si->bitmap = 0;

	return 0;
}