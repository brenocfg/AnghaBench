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
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 scalar_t__ IN_CLASSA (int /*<<< orphan*/ ) ; 
 int IN_CLASSA_NET ; 
 scalar_t__ IN_CLASSB (int /*<<< orphan*/ ) ; 
 int IN_CLASSB_NET ; 
 scalar_t__ IN_CLASSC (int /*<<< orphan*/ ) ; 
 int IN_CLASSC_NET ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static in_addr_t
ipaddrtonetmask(in_addr_t addr)
{

	addr = ntohl(addr);
	if (IN_CLASSA(addr))
		return htonl(IN_CLASSA_NET);
	if (IN_CLASSB(addr))
		return htonl(IN_CLASSB_NET);
	if (IN_CLASSC(addr))
		return htonl(IN_CLASSC_NET);
	logmsg(LOG_DEBUG, "unknown IP address class: %08X", addr);
	return htonl(0xffffffff);
}