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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  EPG5000_NVRAM_ADDR ; 
 int /*<<< orphan*/  EPG5000_NVRAM_SIZE ; 
 scalar_t__ KSEG1ADDR (int /*<<< orphan*/ ) ; 
 int ath79_nvram_parse_mac_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int epg5000_get_mac(const char *name, char *mac)
{
	u8 *nvram = (u8 *) KSEG1ADDR(EPG5000_NVRAM_ADDR);
	int err;

	err = ath79_nvram_parse_mac_addr(nvram, EPG5000_NVRAM_SIZE,
					 name, mac);
	if (err) {
		pr_err("no MAC address found for %s\n", name);
		return false;
	}

	return true;
}