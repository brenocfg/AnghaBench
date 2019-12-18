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
struct TYPE_2__ {int /*<<< orphan*/  grouping; int /*<<< orphan*/  thousands_sep; int /*<<< orphan*/  decimal_point; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  close_category (int /*<<< orphan*/ *) ; 
 TYPE_1__ numeric ; 
 int /*<<< orphan*/ * open_category () ; 
 scalar_t__ putl_category (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dump_numeric(void)
{
	FILE *f;

	if ((f = open_category()) == NULL) {
		return;
	}

	if ((putl_category(numeric.decimal_point, f) == EOF) ||
	    (putl_category(numeric.thousands_sep, f) == EOF) ||
	    (putl_category(numeric.grouping, f) == EOF)) {
		return;
	}
	close_category(f);
}