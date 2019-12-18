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

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 char* ath79_nvram_find_var (char const*,char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int sscanf (char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vfree (char*) ; 
 char* vmalloc (unsigned int) ; 

int ath79_nvram_parse_mac_addr(const char *nvram, unsigned nvram_len,
			       const char *name, char *mac)
{
	char *buf;
	char *mac_str;
	int ret;
	int t;

	buf = vmalloc(nvram_len);
	if (!buf)
		return -ENOMEM;

	memcpy(buf, nvram, nvram_len);
	buf[nvram_len - 1] = '\0';

	mac_str = ath79_nvram_find_var(name, buf, nvram_len);
	if (!mac_str) {
		ret = -EINVAL;
		goto free;
	}

	if (strlen(mac_str) == 19 && mac_str[0] == '"' && mac_str[18] == '"') {
		mac_str[18] = 0;
		mac_str++;
	}

	t = sscanf(mac_str, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
		   &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);

	if (t != ETH_ALEN)
		t = sscanf(mac_str, "%02hhx-%02hhx-%02hhx-%02hhx-%02hhx-%02hhx",
			&mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);

	if (t != ETH_ALEN) {
		ret = -EINVAL;
		goto free;
	}

	ret = 0;

free:
	vfree(buf);
	return ret;
}