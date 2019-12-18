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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mps_describe_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mps_sasdev0_devtype ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*,int /*<<< orphan*/ ) ; 

void
mps_describe_devinfo(uint32_t devinfo, char *string, int len)
{
	snprintf(string, len, "%b,%s", devinfo,
	    "\20" "\4SataHost" "\5SmpInit" "\6StpInit" "\7SspInit"
	    "\10SataDev" "\11SmpTarg" "\12StpTarg" "\13SspTarg" "\14Direct"
	    "\15LsiDev" "\16AtapiDev" "\17SepDev",
	    mps_describe_table(mps_sasdev0_devtype, devinfo & 0x03));
}