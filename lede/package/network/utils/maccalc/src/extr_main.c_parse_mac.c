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
 int ERR_INVALID ; 
 int MAC_ADDRESS_LEN ; 
 int sscanf (char const*,char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int parse_mac(const char *mac_str, unsigned char *buf)
{
	int t;

	t = sscanf(mac_str, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
		   &buf[0], &buf[1], &buf[2], &buf[3], &buf[4], &buf[5]);

	if (t != MAC_ADDRESS_LEN)
		return ERR_INVALID;

	return 0;
}