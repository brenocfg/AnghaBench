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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static char *
lacp_format_mac(const uint8_t *mac, char *buf, size_t buflen)
{
	snprintf(buf, buflen, "%02X-%02X-%02X-%02X-%02X-%02X",
	    (int)mac[0], (int)mac[1], (int)mac[2], (int)mac[3],
	    (int)mac[4], (int)mac[5]);

	return (buf);
}