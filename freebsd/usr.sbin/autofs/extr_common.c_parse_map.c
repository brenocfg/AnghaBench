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
struct node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_MAP_PREFIX ; 
 int /*<<< orphan*/  F_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int auto_pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * auto_popen (char*,char const*,...) ; 
 char* checked_strdup (char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int file_is_executable (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_debugx (char*,char const*,...) ; 
 int /*<<< orphan*/  log_err (int,char*,...) ; 
 int /*<<< orphan*/  log_errx (int,char*,char const*) ; 
 int /*<<< orphan*/  node_expand_direct_maps (struct node*) ; 
 int /*<<< orphan*/  node_expand_includes (struct node*,int) ; 
 void parse_included_map (struct node*,char const*) ; 
 int /*<<< orphan*/  parse_map_yyin (struct node*,char const*,char const*) ; 
 void parse_special_map (struct node*,char const*,char const*) ; 
 int /*<<< orphan*/ * yyin ; 

void
parse_map(struct node *parent, const char *map, const char *key,
    bool *wildcards)
{
	char *path = NULL;
	int error, ret;
	bool executable;

	assert(map != NULL);
	assert(map[0] != '\0');

	log_debugx("parsing map \"%s\"", map);

	if (wildcards != NULL)
		*wildcards = false;

	if (map[0] == '-') {
		if (wildcards != NULL)
			*wildcards = true;
		return (parse_special_map(parent, map, key));
	}

	if (map[0] == '/') {
		path = checked_strdup(map);
	} else {
		ret = asprintf(&path, "%s/%s", AUTO_MAP_PREFIX, map);
		if (ret < 0)
			log_err(1, "asprintf");
		log_debugx("map \"%s\" maps to \"%s\"", map, path);

		/*
		 * See if the file exists.  If not, try to obtain the map
		 * from directory services.
		 */
		error = access(path, F_OK);
		if (error != 0) {
			log_debugx("map file \"%s\" does not exist; falling "
			    "back to directory services", path);
			return (parse_included_map(parent, map));
		}
	}

	executable = file_is_executable(path);

	if (executable) {
		log_debugx("map \"%s\" is executable", map);

		if (wildcards != NULL)
			*wildcards = true;

		if (key != NULL) {
			yyin = auto_popen(path, key, NULL);
		} else {
			yyin = auto_popen(path, NULL);
		}
		assert(yyin != NULL);
	} else {
		yyin = fopen(path, "r");
		if (yyin == NULL)
			log_err(1, "unable to open \"%s\"", path);
	}

	free(path);
	path = NULL;

	parse_map_yyin(parent, map, executable ? key : NULL);

	if (executable) {
		error = auto_pclose(yyin);
		yyin = NULL;
		if (error != 0) {
			log_errx(1, "failed to handle executable map \"%s\"",
			    map);
		}
	} else {
		fclose(yyin);
	}
	yyin = NULL;

	log_debugx("done parsing map \"%s\"", map);

	node_expand_includes(parent, false);
	node_expand_direct_maps(parent);
}