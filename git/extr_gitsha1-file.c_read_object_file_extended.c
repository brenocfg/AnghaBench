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
struct stat {int dummy; } ;
struct repository {int dummy; } ;
struct packed_git {char const* pack_name; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ errno ; 
 struct packed_git* has_packed_and_bad (struct repository*,int /*<<< orphan*/ ) ; 
 struct object_id const* lookup_replace_object (struct repository*,struct object_id const*) ; 
 char const* oid_to_hex (struct object_id const*) ; 
 void* read_object (struct repository*,struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  stat_loose_object (struct repository*,struct object_id const*,struct stat*,char const**) ; 

void *read_object_file_extended(struct repository *r,
				const struct object_id *oid,
				enum object_type *type,
				unsigned long *size,
				int lookup_replace)
{
	void *data;
	const struct packed_git *p;
	const char *path;
	struct stat st;
	const struct object_id *repl = lookup_replace ?
		lookup_replace_object(r, oid) : oid;

	errno = 0;
	data = read_object(r, repl, type, size);
	if (data)
		return data;

	if (errno && errno != ENOENT)
		die_errno(_("failed to read object %s"), oid_to_hex(oid));

	/* die if we replaced an object with one that does not exist */
	if (repl != oid)
		die(_("replacement %s not found for %s"),
		    oid_to_hex(repl), oid_to_hex(oid));

	if (!stat_loose_object(r, repl, &st, &path))
		die(_("loose object %s (stored in %s) is corrupt"),
		    oid_to_hex(repl), path);

	if ((p = has_packed_and_bad(r, repl->hash)) != NULL)
		die(_("packed object %s (stored in %s) is corrupt"),
		    oid_to_hex(repl), p->pack_name);

	return NULL;
}