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
 int os_snprintf (char*,size_t,char*) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 scalar_t__ wpa_snprintf_hex (char*,size_t,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static size_t hostapd_write_ht_mcs_bitmask(char *buf, size_t buflen,
					   size_t curr_len, const u8 *mcs_set)
{
	int ret;
	size_t len = curr_len;

	ret = os_snprintf(buf + len, buflen - len,
			  "ht_mcs_bitmask=");
	if (os_snprintf_error(buflen - len, ret))
		return len;
	len += ret;

	/* 77 first bits (+ 3 reserved bits) */
	len += wpa_snprintf_hex(buf + len, buflen - len, mcs_set, 10);

	ret = os_snprintf(buf + len, buflen - len, "\n");
	if (os_snprintf_error(buflen - len, ret))
		return curr_len;
	len += ret;

	return len;
}