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
typedef  int u_short ;

/* Variables and functions */
 int RES_DONTSERVE ; 
 int RES_DONTTRUST ; 
 int RES_FLAKE ; 
 int RES_IGNORE ; 
 int RES_KOD ; 
 int RES_LIMITED ; 
 int RES_LPTRAP ; 
 int RES_MSSNTP ; 
 int RES_NOEPEER ; 
 int RES_NOMODIFY ; 
 int RES_NOMRULIST ; 
 int RES_NOPEER ; 
 int RES_NOQUERY ; 
 int RES_NOTRAP ; 
 int RES_VERSION ; 
 int /*<<< orphan*/  appendstr (char*,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

char *
build_rflags(u_short rflags)
{
	static char rfs[1024];

	rfs[0] = '\0';

	if (rflags & RES_FLAKE) {
		rflags &= ~RES_FLAKE;
		appendstr(rfs, sizeof rfs, "flake");
	}

	if (rflags & RES_IGNORE) {
		rflags &= ~RES_IGNORE;
		appendstr(rfs, sizeof rfs, "ignore");
	}

	if (rflags & RES_KOD) {
		rflags &= ~RES_KOD;
		appendstr(rfs, sizeof rfs, "kod");
	}

	if (rflags & RES_MSSNTP) {
		rflags &= ~RES_MSSNTP;
		appendstr(rfs, sizeof rfs, "mssntp");
	}

	if (rflags & RES_LIMITED) {
		rflags &= ~RES_LIMITED;
		appendstr(rfs, sizeof rfs, "limited");
	}

	if (rflags & RES_LPTRAP) {
		rflags &= ~RES_LPTRAP;
		appendstr(rfs, sizeof rfs, "lptrap");
	}

	if (rflags & RES_NOMODIFY) {
		rflags &= ~RES_NOMODIFY;
		appendstr(rfs, sizeof rfs, "nomodify");
	}

	if (rflags & RES_NOMRULIST) {
		rflags &= ~RES_NOMRULIST;
		appendstr(rfs, sizeof rfs, "nomrulist");
	}

	if (rflags & RES_NOEPEER) {
		rflags &= ~RES_NOEPEER;
		appendstr(rfs, sizeof rfs, "noepeer");
	}

	if (rflags & RES_NOPEER) {
		rflags &= ~RES_NOPEER;
		appendstr(rfs, sizeof rfs, "nopeer");
	}

	if (rflags & RES_NOQUERY) {
		rflags &= ~RES_NOQUERY;
		appendstr(rfs, sizeof rfs, "noquery");
	}

	if (rflags & RES_DONTSERVE) {
		rflags &= ~RES_DONTSERVE;
		appendstr(rfs, sizeof rfs, "dontserve");
	}

	if (rflags & RES_NOTRAP) {
		rflags &= ~RES_NOTRAP;
		appendstr(rfs, sizeof rfs, "notrap");
	}

	if (rflags & RES_DONTTRUST) {
		rflags &= ~RES_DONTTRUST;
		appendstr(rfs, sizeof rfs, "notrust");
	}

	if (rflags & RES_VERSION) {
		rflags &= ~RES_VERSION;
		appendstr(rfs, sizeof rfs, "version");
	}

	if (rflags) {
		char string[10];

		snprintf(string, sizeof string, "%0x", rflags);
		appendstr(rfs, sizeof rfs, string);
	}

	if ('\0' == rfs[0]) {
		appendstr(rfs, sizeof rfs, "(none)");
	}

	return rfs;
}