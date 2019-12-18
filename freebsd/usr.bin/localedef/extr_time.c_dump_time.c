#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ampm_fmt; scalar_t__ c_fmt; scalar_t__ date_fmt; scalar_t__ pm; scalar_t__ am; scalar_t__ x_fmt; scalar_t__ X_fmt; scalar_t__* weekday; scalar_t__* wday; scalar_t__* month; scalar_t__* mon; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  close_category (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_category () ; 
 scalar_t__ putl_category (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__ tm ; 

void
dump_time(void)
{
	FILE *f;
	int i;

	if ((f = open_category()) == NULL) {
		return;
	}

	for (i = 0; i < 12; i++) {
		if (putl_category(tm.mon[i], f) == EOF) {
			return;
		}
	}
	for (i = 0; i < 12; i++) {
		if (putl_category(tm.month[i], f) == EOF) {
			return;
		}
	}
	for (i = 0; i < 7; i++) {
		if (putl_category(tm.wday[i], f) == EOF) {
			return;
		}
	}
	for (i = 0; i < 7; i++) {
		if (putl_category(tm.weekday[i], f) == EOF) {
			return;
		}
	}

	/*
	 * NOTE: If date_fmt is not specified, then we'll default to
	 * using the %c for date.  This is reasonable for most
	 * locales, although for reasons that I don't understand
	 * Solaris historically has had a separate format for date.
	 */
	if ((putl_category(tm.X_fmt, f) == EOF) ||
	    (putl_category(tm.x_fmt, f) == EOF) ||
	    (putl_category(tm.c_fmt, f) == EOF) ||
	    (putl_category(tm.am, f) == EOF) ||
	    (putl_category(tm.pm, f) == EOF) ||
	    (putl_category(tm.date_fmt ? tm.date_fmt : tm.c_fmt, f) == EOF) ||
	    (putl_category(tm.ampm_fmt, f) == EOF)) {
		return;
	}
	close_category(f);
}