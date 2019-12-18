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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  numbuf ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_DIVISOR_1000 ; 
 int HN_NOSPACE ; 
 scalar_t__ hflag ; 
 int /*<<< orphan*/  humanize_number (char*,int,scalar_t__,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

char *
fmthumanvalinos(int64_t inos)
{
	static char numbuf[20];

	if (hflag) {
		humanize_number(numbuf, inos < 0 ? 7 : 6,
		    inos, "", HN_AUTOSCALE, HN_NOSPACE | HN_DIVISOR_1000);
		return (numbuf);
	}
	snprintf(numbuf, sizeof(numbuf), "%ju", (uintmax_t)inos);
	return(numbuf);
}