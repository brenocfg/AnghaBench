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
typedef  int u_int32 ;

/* Variables and functions */
 int INT_BCASTOPEN ; 
 int INT_BCASTXMIT ; 
 int INT_BROADCAST ; 
 int INT_LOOPBACK ; 
 int INT_MCASTIF ; 
 int INT_MCASTOPEN ; 
 int INT_MULTICAST ; 
 int INT_PPP ; 
 int INT_PRIVACY ; 
 int INT_UP ; 
 int INT_WILDCARD ; 
 int /*<<< orphan*/  appendstr (char*,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

char *
build_iflags(u_int32 iflags)
{
	static char ifs[1024];

	ifs[0] = '\0';

	if (iflags & INT_UP) {
		iflags &= ~INT_UP;
		appendstr(ifs, sizeof ifs, "up");
	}

	if (iflags & INT_PPP) {
		iflags &= ~INT_PPP;
		appendstr(ifs, sizeof ifs, "ppp");
	}

	if (iflags & INT_LOOPBACK) {
		iflags &= ~INT_LOOPBACK;
		appendstr(ifs, sizeof ifs, "loopback");
	}

	if (iflags & INT_BROADCAST) {
		iflags &= ~INT_BROADCAST;
		appendstr(ifs, sizeof ifs, "broadcast");
	}

	if (iflags & INT_MULTICAST) {
		iflags &= ~INT_MULTICAST;
		appendstr(ifs, sizeof ifs, "multicast");
	}

	if (iflags & INT_BCASTOPEN) {
		iflags &= ~INT_BCASTOPEN;
		appendstr(ifs, sizeof ifs, "bcastopen");
	}

	if (iflags & INT_MCASTOPEN) {
		iflags &= ~INT_MCASTOPEN;
		appendstr(ifs, sizeof ifs, "mcastopen");
	}

	if (iflags & INT_WILDCARD) {
		iflags &= ~INT_WILDCARD;
		appendstr(ifs, sizeof ifs, "wildcard");
	}

	if (iflags & INT_MCASTIF) {
		iflags &= ~INT_MCASTIF;
		appendstr(ifs, sizeof ifs, "MCASTif");
	}

	if (iflags & INT_PRIVACY) {
		iflags &= ~INT_PRIVACY;
		appendstr(ifs, sizeof ifs, "IPv6privacy");
	}

	if (iflags & INT_BCASTXMIT) {
		iflags &= ~INT_BCASTXMIT;
		appendstr(ifs, sizeof ifs, "bcastxmit");
	}

	if (iflags) {
		char string[10];

		snprintf(string, sizeof string, "%0x", iflags);
		appendstr(ifs, sizeof ifs, string);
	}

	return ifs;
}