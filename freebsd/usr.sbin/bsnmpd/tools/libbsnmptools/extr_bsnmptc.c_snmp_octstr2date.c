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
 scalar_t__ SNMP_DATETIME_OCTETS ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,char,char,...) ; 

__attribute__((used)) static char *
snmp_octstr2date(uint32_t len, char *octets, char *buf)
{
	int year;
	char *ptr;

	if (len != SNMP_DATETIME_OCTETS || octets == NULL || buf == NULL)
		return (NULL);

	buf[0]= '\0';
	year = (octets[0] << 8);
	year += (octets[1]);

	ptr = buf;
	ptr += sprintf(ptr, "%4.4d-%.2d-%.2d, ", year, octets[2],octets[3]);
	ptr += sprintf(ptr, "%2.2d:%2.2d:%2.2d.%.2d, ", octets[4],octets[5],
	    octets[6],octets[7]);
	ptr += sprintf(ptr, "%c%.2d:%.2d", octets[8],octets[9],octets[10]);

	return (buf);
}