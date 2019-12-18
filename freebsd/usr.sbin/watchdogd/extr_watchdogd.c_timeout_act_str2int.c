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
struct TYPE_2__ {int at_value; int /*<<< orphan*/ * at_act; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 TYPE_1__* act_tbl ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  timeout_act_error (char const*,char*) ; 

__attribute__((used)) static int
timeout_act_str2int(const char *lopt, const char *acts)
{
	int i;
	char *dupacts, *tofree;
	char *o;
	int rv = 0;

	tofree = dupacts = strdup(acts);
	if (!tofree)
		err(EX_OSERR, "malloc");
	while ((o = strsep(&dupacts, ",")) != NULL) {
		for (i = 0; act_tbl[i].at_act != NULL; i++) {
			if (!strcmp(o, act_tbl[i].at_act)) {
				rv |= act_tbl[i].at_value;
				break;
			}
		}
		if (act_tbl[i].at_act == NULL)
			timeout_act_error(lopt, o);
	}
	free(tofree);
	return rv;
}