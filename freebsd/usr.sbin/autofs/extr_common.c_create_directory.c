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
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  assert (int) ; 
 char* checked_strdup (char const*) ; 
 char* concat (char*,char,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_warn (char*,char*) ; 
 int mkdir (char*,int) ; 
 char* strsep (char**,char*) ; 

void
create_directory(const char *path)
{
	char *component, *copy, *tofree, *partial, *tmp;
	int error;

	assert(path[0] == '/');

	/*
	 * +1 to skip the leading slash.
	 */
	copy = tofree = checked_strdup(path + 1);

	partial = checked_strdup("");
	for (;;) {
		component = strsep(&copy, "/");
		if (component == NULL)
			break;
		tmp = concat(partial, '/', component);
		free(partial);
		partial = tmp;
		//log_debugx("creating \"%s\"", partial);
		error = mkdir(partial, 0755);
		if (error != 0 && errno != EEXIST) {
			log_warn("cannot create %s", partial);
			return;
		}
	}

	free(tofree);
}