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
struct stat {scalar_t__ st_mtime; } ;
struct rev_info {int dummy; } ;
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char const*) ; 
 scalar_t__ expire ; 
 scalar_t__ is_object_reachable (struct object_id const*,struct rev_info*) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 
 char* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ show_only ; 
 int /*<<< orphan*/  the_repository ; 
 char* type_name (int) ; 
 int /*<<< orphan*/  unlink_or_warn (char const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int prune_object(const struct object_id *oid, const char *fullpath,
			void *data)
{
	struct rev_info *revs = data;
	struct stat st;

	if (is_object_reachable(oid, revs))
		return 0;

	if (lstat(fullpath, &st)) {
		/* report errors, but do not stop pruning */
		error("Could not stat '%s'", fullpath);
		return 0;
	}
	if (st.st_mtime > expire)
		return 0;
	if (show_only || verbose) {
		enum object_type type = oid_object_info(the_repository, oid,
							NULL);
		printf("%s %s\n", oid_to_hex(oid),
		       (type > 0) ? type_name(type) : "unknown");
	}
	if (!show_only)
		unlink_or_warn(fullpath);
	return 0;
}