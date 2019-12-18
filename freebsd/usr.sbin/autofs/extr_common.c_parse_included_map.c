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
 char const* AUTO_INCLUDE_PATH ; 
 int /*<<< orphan*/  F_OK ; 
 int access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int auto_pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * auto_popen (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_errx (int,char*,char const*) ; 
 int /*<<< orphan*/  node_expand_direct_maps (struct node*) ; 
 int /*<<< orphan*/  node_expand_includes (struct node*,int) ; 
 int /*<<< orphan*/  parse_map_yyin (struct node*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * yyin ; 

__attribute__((used)) static void
parse_included_map(struct node *parent, const char *map)
{
	int error;

	assert(map[0] != '-');
	assert(map[0] != '/');

	error = access(AUTO_INCLUDE_PATH, F_OK);
	if (error != 0) {
		log_errx(1, "directory services not configured;"
		    " %s does not exist", AUTO_INCLUDE_PATH);
	}

	yyin = auto_popen(AUTO_INCLUDE_PATH, map, NULL);
	assert(yyin != NULL);

	parse_map_yyin(parent, map, NULL);

	error = auto_pclose(yyin);
	yyin = NULL;
	if (error != 0)
		log_errx(1, "failed to handle remote map \"%s\"", map);

	node_expand_includes(parent, false);
	node_expand_direct_maps(parent);
}