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
struct archive {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int (* setter ) (struct archive*) ;int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_STATE_FATAL ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__* names ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 int stub1 (struct archive*) ; 

int
archive_write_add_filter_by_name(struct archive *a, const char *name)
{
	int i;

	for (i = 0; names[i].name != NULL; i++) {
		if (strcmp(name, names[i].name) == 0)
			return ((names[i].setter)(a));
	}

	archive_set_error(a, EINVAL, "No such filter '%s'", name);
	a->state = ARCHIVE_STATE_FATAL;
	return (ARCHIVE_FATAL);
}