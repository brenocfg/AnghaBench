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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*,...) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ file_exists (char const*) ; 
 int /*<<< orphan*/  get_tree_entry (struct object_id const*,char*,struct object_id*,unsigned int*) ; 
 scalar_t__ is_missing_file_error (int /*<<< orphan*/ ) ; 
 char* xstrfmt (char*,char const*,char const*) ; 

__attribute__((used)) static void diagnose_invalid_oid_path(const char *prefix,
				      const char *filename,
				      const struct object_id *tree_oid,
				      const char *object_name,
				      int object_name_len)
{
	struct object_id oid;
	unsigned mode;

	if (!prefix)
		prefix = "";

	if (file_exists(filename))
		die("Path '%s' exists on disk, but not in '%.*s'.",
		    filename, object_name_len, object_name);
	if (is_missing_file_error(errno)) {
		char *fullname = xstrfmt("%s%s", prefix, filename);

		if (!get_tree_entry(tree_oid, fullname, &oid, &mode)) {
			die("Path '%s' exists, but not '%s'.\n"
			    "Did you mean '%.*s:%s' aka '%.*s:./%s'?",
			    fullname,
			    filename,
			    object_name_len, object_name,
			    fullname,
			    object_name_len, object_name,
			    filename);
		}
		die("Path '%s' does not exist in '%.*s'",
		    filename, object_name_len, object_name);
	}
}