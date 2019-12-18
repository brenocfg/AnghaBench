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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  fmt ;

/* Variables and functions */
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_DECIMAL ; 
 int HN_NOSPACE ; 
 int /*<<< orphan*/  humanize_number (char*,int,scalar_t__,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  xo_attr (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_emit (char*,int,char*) ; 
 int /*<<< orphan*/  xo_errx (int,char*) ; 

__attribute__((used)) static void
prthuman(const char *name, uint64_t val, int size, int flags)
{
	char buf[10];
	char fmt[128];

	snprintf(fmt, sizeof(fmt), "{:%s/%%*s}", name);

	if (size < 5 || size > 9)
		xo_errx(1, "doofus");
	flags |= HN_NOSPACE | HN_DECIMAL;
	humanize_number(buf, size, val, "", HN_AUTOSCALE, flags);
	xo_attr("value", "%ju", (uintmax_t) val);
	xo_emit(fmt, size, buf);
}