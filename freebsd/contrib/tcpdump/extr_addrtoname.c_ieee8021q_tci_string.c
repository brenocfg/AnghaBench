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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int const,int const,char*) ; 

const char *
ieee8021q_tci_string(const uint16_t tci)
{
	static char buf[128];
	snprintf(buf, sizeof(buf), "vlan %u, p %u%s",
	         tci & 0xfff,
	         tci >> 13,
	         (tci & 0x1000) ? ", DEI" : "");
	return buf;
}