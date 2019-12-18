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
struct adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FW_SCHED_TYPE_PKTSCHED ; 
 int INTR_OK ; 
 int SLEEP_OK ; 
 int begin_synchronized_op (struct adapter*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_sched_config (struct adapter*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
set_sched_class_config(struct adapter *sc, int minmax)
{
	int rc;

	if (minmax < 0)
		return (EINVAL);

	rc = begin_synchronized_op(sc, NULL, SLEEP_OK | INTR_OK, "t4sscc");
	if (rc)
		return (rc);
	rc = -t4_sched_config(sc, FW_SCHED_TYPE_PKTSCHED, minmax, 1);
	end_synchronized_op(sc, 0);

	return (rc);
}