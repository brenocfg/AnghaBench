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
 int /*<<< orphan*/ ** args ; 
 int cargs ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int nargs ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static void
addarg(const char *item)
{
	if (nargs + 1 >= cargs) {
		cargs += 16;
		if ((args = realloc(args, sizeof(*args) * cargs)) == NULL)
			err(1, "malloc");
	}
	if ((args[nargs++] = strdup(item)) == NULL)
		err(1, "strdup");
	args[nargs] = NULL;
}