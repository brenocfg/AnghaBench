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
typedef  char* uintmax_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_B ; 
 int HN_DECIMAL ; 
 int HN_NOSPACE ; 
 int /*<<< orphan*/  dbtob (scalar_t__) ; 
 scalar_t__ dbtokb (scalar_t__) ; 
 int /*<<< orphan*/  hflag ; 
 int /*<<< orphan*/  humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
prthumanval(int64_t blocks)
{
	char buf[7];
	int flags;

	if (!hflag) {
		printf(" %6ju", (uintmax_t)dbtokb(blocks));
		return;
	}
	flags = HN_NOSPACE | HN_DECIMAL;
	if (blocks != 0)
		flags |= HN_B;
	humanize_number(buf, sizeof(buf) - (blocks < 0 ? 0 : 1),
	    dbtob(blocks), "", HN_AUTOSCALE, flags);
	(void)printf("%7s", buf);
}