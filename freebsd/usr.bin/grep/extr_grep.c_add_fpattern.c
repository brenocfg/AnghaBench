#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct epat {int dummy; } ;
struct TYPE_4__ {int mode; int /*<<< orphan*/  pat; } ;

/* Variables and functions */
 TYPE_1__* fpattern ; 
 int fpattern_sz ; 
 int fpatterns ; 
 TYPE_1__* grep_realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  grep_strdup (char const*) ; 

__attribute__((used)) static void
add_fpattern(const char *pat, int mode)
{

	/* Increase size if necessary */
	if (fpatterns == fpattern_sz) {
		fpattern_sz *= 2;
		fpattern = grep_realloc(fpattern, ++fpattern_sz *
		    sizeof(struct epat));
	}
	fpattern[fpatterns].pat = grep_strdup(pat);
	fpattern[fpatterns].mode = mode;
	++fpatterns;
}