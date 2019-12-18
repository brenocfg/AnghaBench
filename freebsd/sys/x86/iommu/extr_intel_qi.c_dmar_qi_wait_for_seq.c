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
struct dmar_unit {int /*<<< orphan*/  inv_seq_waiters; int /*<<< orphan*/  lock; } ;
struct dmar_qi_genseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  dmar_qi_seq_processed (struct dmar_unit*,struct dmar_qi_genseq const*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dmar_qi_wait_for_seq(struct dmar_unit *unit, const struct dmar_qi_genseq *gseq,
    bool nowait)
{

	DMAR_ASSERT_LOCKED(unit);
	unit->inv_seq_waiters++;
	while (!dmar_qi_seq_processed(unit, gseq)) {
		if (cold || nowait) {
			cpu_spinwait();
		} else {
			msleep(&unit->inv_seq_waiters, &unit->lock, 0,
			    "dmarse", hz);
		}
	}
	unit->inv_seq_waiters--;
}