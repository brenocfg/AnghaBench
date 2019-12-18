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
 TYPE_1__* dpattern ; 
 int dpattern_sz ; 
 int dpatterns ; 
 TYPE_1__* grep_realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  grep_strdup (char const*) ; 

__attribute__((used)) static void
add_dpattern(const char *pat, int mode)
{

	/* Increase size if necessary */
	if (dpatterns == dpattern_sz) {
		dpattern_sz *= 2;
		dpattern = grep_realloc(dpattern, ++dpattern_sz *
		    sizeof(struct epat));
	}
	dpattern[dpatterns].pat = grep_strdup(pat);
	dpattern[dpatterns].mode = mode;
	++dpatterns;
}