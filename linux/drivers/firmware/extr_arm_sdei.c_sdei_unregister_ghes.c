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
typedef  int /*<<< orphan*/  u32 ;
struct ghes {TYPE_2__* generic; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {TYPE_1__ notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ACPI_APEI_GHES ; 
 int EINPROGRESS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  schedule () ; 
 int sdei_event_disable (int /*<<< orphan*/ ) ; 
 int sdei_event_unregister (int /*<<< orphan*/ ) ; 

int sdei_unregister_ghes(struct ghes *ghes)
{
	int i;
	int err;
	u32 event_num = ghes->generic->notify.vector;

	might_sleep();

	if (!IS_ENABLED(CONFIG_ACPI_APEI_GHES))
		return -EOPNOTSUPP;

	/*
	 * The event may be running on another CPU. Disable it
	 * to stop new events, then try to unregister a few times.
	 */
	err = sdei_event_disable(event_num);
	if (err)
		return err;

	for (i = 0; i < 3; i++) {
		err = sdei_event_unregister(event_num);
		if (err != -EINPROGRESS)
			break;

		schedule();
	}

	return err;
}