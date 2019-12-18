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
typedef  int /*<<< orphan*/  value ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 

__attribute__((used)) static char *
snmp_oct2bits(uint32_t len, char *octets, char *buf)
{
	int i, bits;
	uint64_t value;

	if (len > sizeof(value) || octets == NULL || buf == NULL)
		return (NULL);

	for (i = len, value = 0, bits = 0; i > 0; i--, bits += 8)
		value += octets[i] << bits;

	buf[0]= '\0';
	sprintf(buf, "0x%llx.",(long long unsigned) value);

	return (buf);
}