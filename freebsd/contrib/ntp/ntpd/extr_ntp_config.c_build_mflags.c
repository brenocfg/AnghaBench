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
 int RESM_NTPONLY ; 
 int RESM_SOURCE ; 
 int /*<<< orphan*/  appendstr (char*,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

char *
build_mflags(u_short mflags)
{
	static char mfs[1024];

	mfs[0] = '\0';

	if (mflags & RESM_NTPONLY) {
		mflags &= ~RESM_NTPONLY;
		appendstr(mfs, sizeof mfs, "ntponly");
	}

	if (mflags & RESM_SOURCE) {
		mflags &= ~RESM_SOURCE;
		appendstr(mfs, sizeof mfs, "source");
	}

	if (mflags) {
		char string[10];

		snprintf(string, sizeof string, "%0x", mflags);
		appendstr(mfs, sizeof mfs, string);
	}

	return mfs;
}