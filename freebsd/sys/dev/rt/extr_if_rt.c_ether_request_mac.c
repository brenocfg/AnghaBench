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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 int /*<<< orphan*/  generate_mac (int*) ; 
 char* kern_getenv (char*) ; 
 int /*<<< orphan*/  macaddr_atoi (char*,int*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  resource_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 

__attribute__((used)) static int
ether_request_mac(device_t dev, uint8_t *mac)
{
	char *var;

	/*
	 * "ethaddr" is passed via envp on RedBoot platforms
	 * "kmac" is passed via argv on RouterBOOT platforms
	 */
#if defined(RT305X_UBOOT) ||  defined(__REDBOOT__) || defined(__ROUTERBOOT__)
	if ((var = kern_getenv("ethaddr")) != NULL ||
	    (var = kern_getenv("kmac")) != NULL ) {

		if(!macaddr_atoi(var, mac)) {
			printf("%s: use %s macaddr from KENV\n",
			    device_get_nameunit(dev), var);
			freeenv(var);
			return (0);
		}
		freeenv(var);
	}
#endif

	/*
	 * Try from hints
	 * hint.[dev].[unit].macaddr
	 */
	if (!resource_string_value(device_get_name(dev),
	    device_get_unit(dev), "macaddr", (const char **)&var)) {

		if(!macaddr_atoi(var, mac)) {
			printf("%s: use %s macaddr from hints\n",
			    device_get_nameunit(dev), var);
			return (0);
		}
	}

#ifdef USE_GENERATED_MAC_ADDRESS
	generate_mac(mac);

	device_printf(dev, "use generated %02x:%02x:%02x:%02x:%02x:%02x "
	    "macaddr\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
#else
	/* Hardcoded */
	mac[0] = 0x00;
	mac[1] = 0x18;
	mac[2] = 0xe7;
	mac[3] = 0xd5;
	mac[4] = 0x83;
	mac[5] = 0x90;

	device_printf(dev, "use hardcoded 00:18:e7:d5:83:90 macaddr\n");
#endif

	return (0);
}