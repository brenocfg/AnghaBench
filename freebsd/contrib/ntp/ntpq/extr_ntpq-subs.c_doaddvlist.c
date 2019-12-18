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
struct varlist {int /*<<< orphan*/ * value; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 void* estrdup (char*) ; 
 struct varlist* findlistvar (struct varlist*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ nextvar (size_t*,char const**,char**,char**) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
doaddvlist(
	struct varlist *vlist,
	const char *vars
	)
{
	struct varlist *vl;
	size_t len;
	char *name;
	char *value;

	len = strlen(vars);
	while (nextvar(&len, &vars, &name, &value)) {
		INSIST(name && value);
		vl = findlistvar(vlist, name);
		if (NULL == vl) {
			fprintf(stderr, "Variable list full\n");
			return;
		}

		if (NULL == vl->name) {
			vl->name = estrdup(name);
		} else if (vl->value != NULL) {
			free(vl->value);
			vl->value = NULL;
		}

		if (value != NULL)
			vl->value = estrdup(value);
	}
}