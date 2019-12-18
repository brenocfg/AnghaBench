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
typedef  int u_long ;
typedef  scalar_t__ u_int32 ;
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 int /*<<< orphan*/  ISREFCLOCKADR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 scalar_t__ SRCADR (int /*<<< orphan*/ *) ; 
 char* clockname (int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 char const* socktoa (int /*<<< orphan*/ *) ; 

const char *
refnumtoa(
	sockaddr_u *num
	)
{
	u_int32 netnum;
	char *buf;
	const char *rclock;

	if (!ISREFCLOCKADR(num))
		return socktoa(num);

	LIB_GETBUF(buf);
	netnum = SRCADR(num);
	rclock = clockname((int)((u_long)netnum >> 8) & 0xff);

	if (rclock != NULL)
		snprintf(buf, LIB_BUFLENGTH, "%s(%lu)",
			 rclock, (u_long)netnum & 0xff);
	else
		snprintf(buf, LIB_BUFLENGTH, "REFCLK(%lu,%lu)",
			 ((u_long)netnum >> 8) & 0xff,
			 (u_long)netnum & 0xff);

	return buf;
}