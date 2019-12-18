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
 scalar_t__ SNMP_NTP_TS_OCTETS ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static char *
snmp_oct2ntp_ts(uint32_t len, char *octets, char *buf)
{
	char *ptr;
	uint32_t i;

	if (len != SNMP_NTP_TS_OCTETS || octets == NULL || buf == NULL)
		return (NULL);

	buf[0]= '\0';

	ptr = buf;
	i = octets[0] * 1000 + octets[1] * 100 + octets[2] * 10 + octets[3];
	ptr += sprintf(ptr, "%4.4d", i);
	i = octets[4] * 1000 + octets[5] * 100 + octets[6] * 10 + octets[7];
	ptr += sprintf(ptr, ".%4.4d", i);

	return (buf);
}