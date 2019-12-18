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
struct gv_volume {int /*<<< orphan*/  name; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (struct gv_volume*) ; 
 struct gv_volume* gv_alloc_volume () ; 
 int /*<<< orphan*/  gv_volstatei (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

struct gv_volume *
gv_new_volume(int max, char *token[])
{
	struct gv_volume *v;
	int j, errors;

	if (token[1] == NULL || *token[1] == '\0')
		return (NULL);

	v = gv_alloc_volume();
	if (v == NULL)
		return (NULL);

	errors = 0;
	for (j = 1; j < max; j++) {
		if (!strcmp(token[j], "state")) {
			j++;
			if (j >= max) {
				errors++;
				break;
			}
			v->state = gv_volstatei(token[j]);
		} else {
			/* We assume this is the volume name. */
			strlcpy(v->name, token[j], sizeof(v->name));
		}
	}

	if (strlen(v->name) == 0)
		errors++;

	if (errors) {
		g_free(v);
		return (NULL);
	}

	return (v);
}