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
struct arglist {int argc; int maxc; int /*<<< orphan*/ ** argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static void
addarg(struct arglist *al, const char *arg)
{

	if (al->argc == al->maxc) {
		al->maxc <<= 1;
		al->argv = realloc(al->argv, al->maxc * sizeof(char *));
		if (al->argv == NULL)
			err(EX_TEMPFAIL, "realloc");
	}
	if (arg == NULL)
		al->argv[al->argc++] = NULL;
	else if ((al->argv[al->argc++] = strdup(arg)) == NULL)
		err(EX_TEMPFAIL, "strdup");
}