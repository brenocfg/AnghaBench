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
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 int settimeofday (struct timeval const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
OS_setSystemDate(const struct timeval *timeval_to_set)
{
	if (settimeofday(timeval_to_set, NULL) == -1) {
		syslog(LOG_ERR, "settimeofday failed: %m");
		return (SNMP_ERR_GENERR);
	}
	return (SNMP_ERR_NOERROR);
}