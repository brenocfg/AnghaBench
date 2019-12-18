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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  macaddr ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  ar71xx_board_mac_addr ; 
 int /*<<< orphan*/  ar71xx_mac_addr_init (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 char* kern_getenv (char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static int
ar71xx_redboot_get_macaddr(void)
{
	char *var;
	int count = 0, i;
	uint32_t macaddr[ETHER_ADDR_LEN];
	uint8_t tmpmac[ETHER_ADDR_LEN];

	/*
	 * "ethaddr" is passed via envp on RedBoot platforms
	 * "kmac" is passed via argv on RouterBOOT platforms
	 */
	if ((var = kern_getenv("ethaddr")) != NULL ||
	    (var = kern_getenv("kmac")) != NULL) {
		count = sscanf(var, "%x%*c%x%*c%x%*c%x%*c%x%*c%x",
		    &macaddr[0], &macaddr[1],
		    &macaddr[2], &macaddr[3],
		    &macaddr[4], &macaddr[5]);

		if (count < 6) {
			memset(macaddr, 0,
			    sizeof(macaddr));
		} else {
			for (i = 0; i < ETHER_ADDR_LEN; i++)
				tmpmac[i] = macaddr[i] & 0xff;
			(void) ar71xx_mac_addr_init(ar71xx_board_mac_addr,
			    tmpmac,
			    0, /* offset */
			    0); /* is_local */
		}
		freeenv(var);
		return (0);
	}
	return (-1);
}