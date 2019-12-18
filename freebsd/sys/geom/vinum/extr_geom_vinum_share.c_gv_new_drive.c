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
struct gv_drive {int /*<<< orphan*/  device; int /*<<< orphan*/  name; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (struct gv_drive*) ; 
 struct gv_drive* gv_alloc_drive () ; 
 int /*<<< orphan*/  gv_drivestatei (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

struct gv_drive *
gv_new_drive(int max, char *token[])
{
	struct gv_drive *d;
	int j, errors;
	char *ptr;

	if (token[1] == NULL || *token[1] == '\0')
		return (NULL);
	d = gv_alloc_drive();
	if (d == NULL)
		return (NULL);
	errors = 0;
	for (j = 1; j < max; j++) {
		if (!strcmp(token[j], "state")) {
			j++;
			if (j >= max) {
				errors++;
				break;
			}
			d->state = gv_drivestatei(token[j]);
		} else if (!strcmp(token[j], "device")) {
			j++;
			if (j >= max) {
				errors++;
				break;
			}
			ptr = token[j];

			if (strncmp(ptr, "/dev/", 5) == 0)
				ptr += 5;
			strlcpy(d->device, ptr, sizeof(d->device));
		} else {
			/* We assume this is the drive name. */
			strlcpy(d->name, token[j], sizeof(d->name));
		}
	}

	if (strlen(d->name) == 0 || strlen(d->device) == 0)
		errors++;

	if (errors) {
		g_free(d);
		return (NULL);
	}

	return (d);
}