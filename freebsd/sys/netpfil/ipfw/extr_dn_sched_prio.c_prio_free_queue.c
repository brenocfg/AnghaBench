#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct prio_si {int /*<<< orphan*/  bitmap; struct dn_queue** q_array; } ;
struct dn_queue {scalar_t__ _si; TYPE_2__* fs; } ;
struct TYPE_3__ {int* par; } ;
struct TYPE_4__ {TYPE_1__ fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
prio_free_queue(struct dn_queue *q)
{
	int prio = q->fs->fs.par[0];
	struct prio_si *si = (struct prio_si *)(q->_si + 1);

	if (si->q_array[prio] == q) {
		si->q_array[prio] = NULL;
		__clear_bit(prio, &si->bitmap);
	}
	return 0;
}