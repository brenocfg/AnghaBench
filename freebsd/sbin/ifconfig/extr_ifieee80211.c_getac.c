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
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
getac(const char *ac)
{
	if (strcasecmp(ac, "ac_be") == 0 || strcasecmp(ac, "be") == 0)
		return WME_AC_BE;
	if (strcasecmp(ac, "ac_bk") == 0 || strcasecmp(ac, "bk") == 0)
		return WME_AC_BK;
	if (strcasecmp(ac, "ac_vi") == 0 || strcasecmp(ac, "vi") == 0)
		return WME_AC_VI;
	if (strcasecmp(ac, "ac_vo") == 0 || strcasecmp(ac, "vo") == 0)
		return WME_AC_VO;
	errx(1, "unknown wme access class %s", ac);
}