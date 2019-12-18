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

/* Variables and functions */
 int /*<<< orphan*/  NTP_OID_RO (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntpEntSoftwareName ; 
 int /*<<< orphan*/  ntpEntSoftwareVendor ; 
 int /*<<< orphan*/  ntpEntSoftwareVersion ; 
 int /*<<< orphan*/  ntpEntSystemType ; 
 int /*<<< orphan*/  ntpEntTimeDistance ; 
 int /*<<< orphan*/  ntpEntTimePrecision ; 
 int /*<<< orphan*/  ntpEntTimeResolution ; 

void
init_ntpSnmpSubagentObject(void)
{
	/* Register all MIB objects with the agentx master */
	NTP_OID_RO( ntpEntSoftwareName,		1, 1, 1, 0);
	NTP_OID_RO( ntpEntSoftwareVersion,	1, 1, 2, 0);
	NTP_OID_RO( ntpEntSoftwareVendor,	1, 1, 3, 0);
	NTP_OID_RO( ntpEntSystemType,		1, 1, 4, 0);
	NTP_OID_RO( ntpEntTimeResolution,	1, 1, 5, 0);
	NTP_OID_RO( ntpEntTimePrecision,	1, 1, 6, 0);
	NTP_OID_RO( ntpEntTimeDistance,		1, 1, 7, 0);
}