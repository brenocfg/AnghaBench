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
typedef  unsigned int uint8_t ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int
dme_parse_macaddr(const char *str, uint8_t *mac)
{
	int count, i;
	unsigned int amac[ETHER_ADDR_LEN];	/* Aligned version */

	count = sscanf(str, "%x%*c%x%*c%x%*c%x%*c%x%*c%x",
	    &amac[0], &amac[1], &amac[2],
	    &amac[3], &amac[4], &amac[5]);
	if (count < ETHER_ADDR_LEN) {
		memset(mac, 0, ETHER_ADDR_LEN);
		return (1);
	}

	/* Copy aligned to result */
	for (i = 0; i < ETHER_ADDR_LEN; i ++)
		mac[i] = (amac[i] & 0xff);

	return (0);
}