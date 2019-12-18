#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
struct TYPE_6__ {scalar_t__ re_nsub; } ;
typedef  TYPE_2__ regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  addchars (char const*,int) ; 
 int /*<<< orphan*/  m4_warnx (char*,int) ; 

__attribute__((used)) static void
add_sub(int n, const char *string, regex_t *re, regmatch_t *pm)
{
	if (n > (int)re->re_nsub)
		m4_warnx("No subexpression %d", n);
	/* Subexpressions that did not match are
	 * not an error.  */
	else if (pm[n].rm_so != -1 &&
	    pm[n].rm_eo != -1) {
		addchars(string + pm[n].rm_so,
			pm[n].rm_eo - pm[n].rm_so);
	}
}