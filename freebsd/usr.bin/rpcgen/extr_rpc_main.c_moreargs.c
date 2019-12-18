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

/* Variables and functions */
 int INT_MAX ; 
 char** arglist ; 
 int argmax ; 
 int /*<<< orphan*/  crash () ; 
 int /*<<< orphan*/  free (char**) ; 
 char** realloc (char**,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
moreargs(void)
{
	char **newarglist;

	argmax = argmax == 0 ? 32 : argmax << 1;
	if (argmax > INT_MAX / 4) {
		warnx("refusing to allocate too many arguments");
		crash();
	}
	newarglist = realloc(arglist, argmax * sizeof(*arglist));
	if (newarglist == NULL) {
		warnx("unable to allocate arglist");
		crash();
	}
	free(arglist);
	arglist = newarglist;
}