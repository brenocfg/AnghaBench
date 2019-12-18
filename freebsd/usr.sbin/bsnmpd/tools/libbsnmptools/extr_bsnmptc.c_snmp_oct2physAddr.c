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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ SNMP_PHYSADDR_OCTETS ; 
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 

__attribute__((used)) static char *
snmp_oct2physAddr(uint32_t len, char *octets, char *buf)
{
	char *ptr;
	uint32_t i;

	if (len != SNMP_PHYSADDR_OCTETS || octets == NULL || buf == NULL)
		return (NULL);

	buf[0]= '\0';

	ptr = buf;
	ptr += sprintf(ptr, "%2.2x", octets[0]);
	for (i = 1; i < 6; i++)
		ptr += sprintf(ptr, ":%2.2x", octets[i]);

	return (buf);
}