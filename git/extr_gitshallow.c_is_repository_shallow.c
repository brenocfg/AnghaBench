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
struct repository {TYPE_1__* parsed_objects; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {char* alternate_shallow_file; int is_shallow; int /*<<< orphan*/  shallow_stat; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ get_oid_hex (char*,struct object_id*) ; 
 char* git_path_shallow (struct repository*) ; 
 int /*<<< orphan*/  register_shallow (struct repository*,struct object_id*) ; 
 int /*<<< orphan*/  stat_validity_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_validity_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int is_repository_shallow(struct repository *r)
{
	/*
	 * NEEDSWORK: This function updates
	 * r->parsed_objects->{is_shallow,shallow_stat} as a side effect but
	 * there is no corresponding function to clear them when the shallow
	 * file is updated.
	 */

	FILE *fp;
	char buf[1024];
	const char *path = r->parsed_objects->alternate_shallow_file;

	if (r->parsed_objects->is_shallow >= 0)
		return r->parsed_objects->is_shallow;

	if (!path)
		path = git_path_shallow(r);
	/*
	 * fetch-pack sets '--shallow-file ""' as an indicator that no
	 * shallow file should be used. We could just open it and it
	 * will likely fail. But let's do an explicit check instead.
	 */
	if (!*path || (fp = fopen(path, "r")) == NULL) {
		stat_validity_clear(r->parsed_objects->shallow_stat);
		r->parsed_objects->is_shallow = 0;
		return r->parsed_objects->is_shallow;
	}
	stat_validity_update(r->parsed_objects->shallow_stat, fileno(fp));
	r->parsed_objects->is_shallow = 1;

	while (fgets(buf, sizeof(buf), fp)) {
		struct object_id oid;
		if (get_oid_hex(buf, &oid))
			die("bad shallow line: %s", buf);
		register_shallow(r, &oid);
	}
	fclose(fp);
	return r->parsed_objects->is_shallow;
}