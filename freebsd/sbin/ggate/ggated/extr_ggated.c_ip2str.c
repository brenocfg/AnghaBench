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
typedef  int /*<<< orphan*/  sip ;
typedef  int in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int) ; 

__attribute__((used)) static char *
ip2str(in_addr_t ip)
{
	static char sip[16];

	snprintf(sip, sizeof(sip), "%u.%u.%u.%u",
	    ((ip >> 24) & 0xff),
	    ((ip >> 16) & 0xff),
	    ((ip >> 8) & 0xff),
	    (ip & 0xff));
	return (sip);
}