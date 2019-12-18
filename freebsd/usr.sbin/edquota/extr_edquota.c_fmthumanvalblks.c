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
 int /*<<< orphan*/  HN_NOSPACE ; 
 int /*<<< orphan*/  dbtob (scalar_t__) ; 
 scalar_t__ dbtokb (scalar_t__) ; 
 scalar_t__ hflag ; 
 int /*<<< orphan*/  humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

char *
fmthumanvalblks(int64_t blocks)
{
	static char numbuf[20];

	if (hflag) {
		humanize_number(numbuf, blocks < 0 ? 7 : 6,
		    dbtob(blocks), "", HN_AUTOSCALE, HN_NOSPACE);
		return (numbuf);
	}
	snprintf(numbuf, sizeof(numbuf), "%juk", (uintmax_t)dbtokb(blocks));
	return(numbuf);
}