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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EC_EVT_TIMING_EVENT ; 
 int /*<<< orphan*/  ACPI_EC_EVT_TIMING_QUERY ; 
 int /*<<< orphan*/  ACPI_EC_EVT_TIMING_STATUS ; 
 int EINVAL ; 
 int /*<<< orphan*/  ec_event_clearing ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int param_set_event_clearing(const char *val,
				    const struct kernel_param *kp)
{
	int result = 0;

	if (!strncmp(val, "status", sizeof("status") - 1)) {
		ec_event_clearing = ACPI_EC_EVT_TIMING_STATUS;
		pr_info("Assuming SCI_EVT clearing on EC_SC accesses\n");
	} else if (!strncmp(val, "query", sizeof("query") - 1)) {
		ec_event_clearing = ACPI_EC_EVT_TIMING_QUERY;
		pr_info("Assuming SCI_EVT clearing on QR_EC writes\n");
	} else if (!strncmp(val, "event", sizeof("event") - 1)) {
		ec_event_clearing = ACPI_EC_EVT_TIMING_EVENT;
		pr_info("Assuming SCI_EVT clearing on event reads\n");
	} else
		result = -EINVAL;
	return result;
}