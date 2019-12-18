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
struct tag {int dummy; } ;
struct object_id {int dummy; } ;
struct commit_extra_header {int /*<<< orphan*/  len; int /*<<< orphan*/  value; } ;
struct commit {int dummy; } ;
struct check_mergetag_data {char** argv; int argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_TAG ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 int /*<<< orphan*/  get_tagged_oid (struct tag*) ; 
 int /*<<< orphan*/  hash_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 
 struct tag* lookup_tag (int /*<<< orphan*/ ,struct object_id*) ; 
 char* oid_to_hex (struct object_id*) ; 
 scalar_t__ oideq (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ parse_tag_buffer (int /*<<< orphan*/ ,struct tag*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  type_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_one_mergetag(struct commit *commit,
			       struct commit_extra_header *extra,
			       void *data)
{
	struct check_mergetag_data *mergetag_data = (struct check_mergetag_data *)data;
	const char *ref = mergetag_data->argv[0];
	struct object_id tag_oid;
	struct tag *tag;
	int i;

	hash_object_file(extra->value, extra->len, type_name(OBJ_TAG), &tag_oid);
	tag = lookup_tag(the_repository, &tag_oid);
	if (!tag)
		return error(_("bad mergetag in commit '%s'"), ref);
	if (parse_tag_buffer(the_repository, tag, extra->value, extra->len))
		return error(_("malformed mergetag in commit '%s'"), ref);

	/* iterate over new parents */
	for (i = 1; i < mergetag_data->argc; i++) {
		struct object_id oid;
		if (get_oid(mergetag_data->argv[i], &oid) < 0)
			return error(_("not a valid object name: '%s'"),
				     mergetag_data->argv[i]);
		if (oideq(get_tagged_oid(tag), &oid))
			return 0; /* found */
	}

	return error(_("original commit '%s' contains mergetag '%s' that is "
		       "discarded; use --edit instead of --graft"), ref,
		     oid_to_hex(&tag_oid));
}