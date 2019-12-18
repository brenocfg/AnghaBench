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
struct TYPE_2__ {char const* path; } ;
struct tree_desc {TYPE_1__ entry; scalar_t__ size; } ;
struct object_id {unsigned char* hash; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (unsigned short) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hashcpy (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,char*,unsigned long) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 char* strchrnul (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  tree_entry_extract (struct tree_desc*,char const**,unsigned short*) ; 
 int /*<<< orphan*/  tree_type ; 
 int /*<<< orphan*/  update_tree_entry (struct tree_desc*) ; 
 int write_object_file (char*,unsigned long,int /*<<< orphan*/ ,struct object_id*) ; 

__attribute__((used)) static int splice_tree(const struct object_id *oid1, const char *prefix,
		       const struct object_id *oid2, struct object_id *result)
{
	char *subpath;
	int toplen;
	char *buf;
	unsigned long sz;
	struct tree_desc desc;
	unsigned char *rewrite_here;
	const struct object_id *rewrite_with;
	struct object_id subtree;
	enum object_type type;
	int status;

	subpath = strchrnul(prefix, '/');
	toplen = subpath - prefix;
	if (*subpath)
		subpath++;

	buf = read_object_file(oid1, &type, &sz);
	if (!buf)
		die("cannot read tree %s", oid_to_hex(oid1));
	init_tree_desc(&desc, buf, sz);

	rewrite_here = NULL;
	while (desc.size) {
		const char *name;
		unsigned short mode;

		tree_entry_extract(&desc, &name, &mode);
		if (strlen(name) == toplen &&
		    !memcmp(name, prefix, toplen)) {
			if (!S_ISDIR(mode))
				die("entry %s in tree %s is not a tree", name,
				    oid_to_hex(oid1));

			/*
			 * We cast here for two reasons:
			 *
			 *   - to flip the "char *" (for the path) to "unsigned
			 *     char *" (for the hash stored after it)
			 *
			 *   - to discard the "const"; this is OK because we
			 *     know it points into our non-const "buf"
			 */
			rewrite_here = (unsigned char *)(desc.entry.path +
							 strlen(desc.entry.path) +
							 1);
			break;
		}
		update_tree_entry(&desc);
	}
	if (!rewrite_here)
		die("entry %.*s not found in tree %s", toplen, prefix,
		    oid_to_hex(oid1));
	if (*subpath) {
		struct object_id tree_oid;
		hashcpy(tree_oid.hash, rewrite_here);
		status = splice_tree(&tree_oid, subpath, oid2, &subtree);
		if (status)
			return status;
		rewrite_with = &subtree;
	} else {
		rewrite_with = oid2;
	}
	hashcpy(rewrite_here, rewrite_with->hash);
	status = write_object_file(buf, sz, tree_type, result);
	free(buf);
	return status;
}