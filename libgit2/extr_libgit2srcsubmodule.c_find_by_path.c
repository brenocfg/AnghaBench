#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ fbp_data ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__strndup (char const*,int) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int find_by_path(const git_config_entry *entry, void *payload)
{
	fbp_data *data = payload;

	if (!strcmp(entry->value, data->path)) {
		const char *fdot, *ldot;
		fdot = strchr(entry->name, '.');
		ldot = strrchr(entry->name, '.');
		data->name = git__strndup(fdot + 1, ldot - fdot - 1);
		GIT_ERROR_CHECK_ALLOC(data->name);
	}

	return 0;
}