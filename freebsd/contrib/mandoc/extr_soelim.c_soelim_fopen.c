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
typedef  int /*<<< orphan*/  path ;
struct TYPE_2__ {size_t sl_cur; char** sl_str; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 TYPE_1__* includes ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static FILE *
soelim_fopen(const char *name)
{
	FILE *f;
	char path[PATH_MAX];
	size_t i;

	if (strcmp(name, "-") == 0)
		return (stdin);

	if ((f = fopen(name, "r")) != NULL)
		return (f);

	if (*name == '/') {
		warn("can't open '%s'", name);
		return (NULL);
	}

	for (i = 0; i < includes->sl_cur; i++) {
		snprintf(path, sizeof(path), "%s/%s", includes->sl_str[i],
		    name);
		if ((f = fopen(path, "r")) != NULL)
			return (f);
	}

	warn("can't open '%s'", name);

	return (f);
}