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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  Aflag ; 
 int /*<<< orphan*/  DEV_BSIZE ; 
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_B ; 
 int HN_DECIMAL ; 
 int HN_DIVISOR_1000 ; 
 int HN_NOSPACE ; 
 scalar_t__ UNITS_SI ; 
 int /*<<< orphan*/  cblocksize ; 
 scalar_t__ hflag ; 
 int /*<<< orphan*/  humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
prthumanval(int64_t bytes)
{
	char buf[5];
	int flags;

	bytes *= cblocksize;
	flags = HN_B | HN_NOSPACE | HN_DECIMAL;
	if (!Aflag)
		bytes *= DEV_BSIZE;
	if (hflag == UNITS_SI)
		flags |= HN_DIVISOR_1000;

	humanize_number(buf, sizeof(buf), bytes, "", HN_AUTOSCALE, flags);

	(void)printf("%4s", buf);
}