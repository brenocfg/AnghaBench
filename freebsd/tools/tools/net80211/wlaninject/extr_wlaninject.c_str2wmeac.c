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
 int WME_AC_BE ; 
 int WME_AC_BK ; 
 int WME_AC_VI ; 
 int WME_AC_VO ; 
 scalar_t__ equal (char const*,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 

int str2wmeac(const char *ac)
{
#define	equal(a,b)	(strcasecmp(a,b) == 0)
	if (equal(ac, "ac_be") || equal(ac, "be"))
		return WME_AC_BE;
	if (equal(ac, "ac_bk") || equal(ac, "bk"))
		return WME_AC_BK;
	if (equal(ac, "ac_vi") || equal(ac, "vi"))
		return WME_AC_VI;
	if (equal(ac, "ac_vo") || equal(ac, "vo"))
		return WME_AC_VO;
	errx(1, "unknown wme access class %s", ac);
#undef equal
}