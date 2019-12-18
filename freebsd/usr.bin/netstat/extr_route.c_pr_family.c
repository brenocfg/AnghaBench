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
#define  AF_CCITT 132 
#define  AF_INET 131 
#define  AF_INET6 130 
#define  AF_ISO 129 
#define  AF_NETGRAPH 128 
 int /*<<< orphan*/  xo_emit (char*,...) ; 

void
pr_family(int af1)
{
	const char *afname;

	switch (af1) {
	case AF_INET:
		afname = "Internet";
		break;
#ifdef INET6
	case AF_INET6:
		afname = "Internet6";
		break;
#endif /*INET6*/
	case AF_ISO:
		afname = "ISO";
		break;
	case AF_CCITT:
		afname = "X.25";
		break;
	case AF_NETGRAPH:
		afname = "Netgraph";
		break;
	default:
		afname = NULL;
		break;
	}
	if (afname)
		xo_emit("\n{k:address-family/%s}:\n", afname);
	else
		xo_emit("\n{L:Protocol Family} {k:address-family/%d}:\n", af1);
}