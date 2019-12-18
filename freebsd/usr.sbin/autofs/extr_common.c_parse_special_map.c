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
 int /*<<< orphan*/  AUTO_SPECIAL_PREFIX ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int auto_pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * auto_popen (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_errx (int,char*,char const*) ; 
 int /*<<< orphan*/  node_expand_direct_maps (struct node*) ; 
 int /*<<< orphan*/  node_expand_includes (struct node*,int) ; 
 int /*<<< orphan*/  parse_map_keys_yyin (struct node*,char const*) ; 
 int /*<<< orphan*/  parse_map_yyin (struct node*,char const*,char const*) ; 
 int /*<<< orphan*/ * yyin ; 

__attribute__((used)) static void
parse_special_map(struct node *parent, const char *map, const char *key)
{
	char *path;
	int error, ret;

	assert(map[0] == '-');

	/*
	 * +1 to skip leading "-" in map name.
	 */
	ret = asprintf(&path, "%s/special_%s", AUTO_SPECIAL_PREFIX, map + 1);
	if (ret < 0)
		log_err(1, "asprintf");

	yyin = auto_popen(path, key, NULL);
	assert(yyin != NULL);

	if (key == NULL) {
		parse_map_keys_yyin(parent, map);
	} else {
		parse_map_yyin(parent, map, key);
	}

	error = auto_pclose(yyin);
	yyin = NULL;
	if (error != 0)
		log_errx(1, "failed to handle special map \"%s\"", map);

	node_expand_includes(parent, false);
	node_expand_direct_maps(parent);

	free(path);
}