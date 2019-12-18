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
 int /*<<< orphan*/  EDAC_REPORTING_DISABLED ; 
 int /*<<< orphan*/  EDAC_REPORTING_ENABLED ; 
 int /*<<< orphan*/  EDAC_REPORTING_FORCE ; 
 int EINVAL ; 
 int /*<<< orphan*/  edac_report ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int edac_report_set(const char *str, const struct kernel_param *kp)
{
	if (!str)
		return -EINVAL;

	if (!strncmp(str, "on", 2))
		edac_report = EDAC_REPORTING_ENABLED;
	else if (!strncmp(str, "off", 3))
		edac_report = EDAC_REPORTING_DISABLED;
	else if (!strncmp(str, "force", 5))
		edac_report = EDAC_REPORTING_FORCE;

	return 0;
}