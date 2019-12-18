#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_2__ {int length; size_t count; int major; int minor; scalar_t__ enabled_memory; scalar_t__ old_enabled_memory; scalar_t__ enabled_sockets; scalar_t__ populated_sockets; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 TYPE_1__ smbios ; 
 int /*<<< orphan*/ * smbios_parse_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smbios_probe (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__,...) ; 

void
smbios_detect(const caddr_t addr)
{
	char		buf[16];
	caddr_t		dmi;
	size_t		i;

	smbios_probe(addr);
	if (smbios.addr == NULL)
		return;

	for (dmi = smbios.addr, i = 0;
	     dmi < smbios.addr + smbios.length && i < smbios.count; i++)
		dmi = smbios_parse_table(dmi);

	sprintf(buf, "%d.%d", smbios.major, smbios.minor);
	setenv("smbios.version", buf, 1);
	if (smbios.enabled_memory > 0 || smbios.old_enabled_memory > 0) {
		sprintf(buf, "%u", smbios.enabled_memory > 0 ?
		    smbios.enabled_memory : smbios.old_enabled_memory);
		setenv("smbios.memory.enabled", buf, 1);
	}
	if (smbios.enabled_sockets > 0) {
		sprintf(buf, "%u", smbios.enabled_sockets);
		setenv("smbios.socket.enabled", buf, 1);
	}
	if (smbios.populated_sockets > 0) {
		sprintf(buf, "%u", smbios.populated_sockets);
		setenv("smbios.socket.populated", buf, 1);
	}
}