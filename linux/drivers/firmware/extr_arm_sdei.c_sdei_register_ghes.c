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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ghes {TYPE_2__* generic; } ;
typedef  int /*<<< orphan*/  sdei_event_callback ;
struct TYPE_3__ {scalar_t__ vector; } ;
struct TYPE_4__ {TYPE_1__ notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ACPI_APEI_GHES ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDEI_EVENT_INFO_EV_PRIORITY ; 
 scalar_t__ SDEI_EVENT_PRIORITY_CRITICAL ; 
 int sdei_api_event_get_info (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int sdei_event_enable (scalar_t__) ; 
 int sdei_event_register (scalar_t__,int /*<<< orphan*/ *,struct ghes*) ; 

int sdei_register_ghes(struct ghes *ghes, sdei_event_callback *normal_cb,
		       sdei_event_callback *critical_cb)
{
	int err;
	u64 result;
	u32 event_num;
	sdei_event_callback *cb;

	if (!IS_ENABLED(CONFIG_ACPI_APEI_GHES))
		return -EOPNOTSUPP;

	event_num = ghes->generic->notify.vector;
	if (event_num == 0) {
		/*
		 * Event 0 is reserved by the specification for
		 * SDEI_EVENT_SIGNAL.
		 */
		return -EINVAL;
	}

	err = sdei_api_event_get_info(event_num, SDEI_EVENT_INFO_EV_PRIORITY,
				      &result);
	if (err)
		return err;

	if (result == SDEI_EVENT_PRIORITY_CRITICAL)
		cb = critical_cb;
	else
		cb = normal_cb;

	err = sdei_event_register(event_num, cb, ghes);
	if (!err)
		err = sdei_event_enable(event_num);

	return err;
}