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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct object {struct object_id oid; int /*<<< orphan*/  parsed; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 unsigned int GET_OID_COMMITTISH ; 
 unsigned int GET_OID_DISAMBIGUATORS ; 
 unsigned int GET_OID_TREEISH ; 
 unsigned int OBJ_ANY ; 
 unsigned int OBJ_BLOB ; 
 unsigned int OBJ_COMMIT ; 
 unsigned int OBJ_NONE ; 
 unsigned int OBJ_TAG ; 
 unsigned int OBJ_TREE ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 struct object* deref_tag (struct repository*,struct object*,char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_oid_1 (struct repository*,char const*,int,struct object_id*,unsigned int) ; 
 int get_oid_oneline (struct repository*,char*,struct object_id*,struct commit_list*) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 struct object* parse_object (struct repository*,struct object_id*) ; 
 struct object* repo_peel_to_type (struct repository*,char const*,int,struct object*,unsigned int) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 char* xstrndup (char const*,int) ; 

__attribute__((used)) static int peel_onion(struct repository *r, const char *name, int len,
		      struct object_id *oid, unsigned lookup_flags)
{
	struct object_id outer;
	const char *sp;
	unsigned int expected_type = 0;
	struct object *o;

	/*
	 * "ref^{type}" dereferences ref repeatedly until you cannot
	 * dereference anymore, or you get an object of given type,
	 * whichever comes first.  "ref^{}" means just dereference
	 * tags until you get a non-tag.  "ref^0" is a shorthand for
	 * "ref^{commit}".  "commit^{tree}" could be used to find the
	 * top-level tree of the given commit.
	 */
	if (len < 4 || name[len-1] != '}')
		return -1;

	for (sp = name + len - 1; name <= sp; sp--) {
		int ch = *sp;
		if (ch == '{' && name < sp && sp[-1] == '^')
			break;
	}
	if (sp <= name)
		return -1;

	sp++; /* beginning of type name, or closing brace for empty */
	if (starts_with(sp, "commit}"))
		expected_type = OBJ_COMMIT;
	else if (starts_with(sp, "tag}"))
		expected_type = OBJ_TAG;
	else if (starts_with(sp, "tree}"))
		expected_type = OBJ_TREE;
	else if (starts_with(sp, "blob}"))
		expected_type = OBJ_BLOB;
	else if (starts_with(sp, "object}"))
		expected_type = OBJ_ANY;
	else if (sp[0] == '}')
		expected_type = OBJ_NONE;
	else if (sp[0] == '/')
		expected_type = OBJ_COMMIT;
	else
		return -1;

	lookup_flags &= ~GET_OID_DISAMBIGUATORS;
	if (expected_type == OBJ_COMMIT)
		lookup_flags |= GET_OID_COMMITTISH;
	else if (expected_type == OBJ_TREE)
		lookup_flags |= GET_OID_TREEISH;

	if (get_oid_1(r, name, sp - name - 2, &outer, lookup_flags))
		return -1;

	o = parse_object(r, &outer);
	if (!o)
		return -1;
	if (!expected_type) {
		o = deref_tag(r, o, name, sp - name - 2);
		if (!o || (!o->parsed && !parse_object(r, &o->oid)))
			return -1;
		oidcpy(oid, &o->oid);
		return 0;
	}

	/*
	 * At this point, the syntax look correct, so
	 * if we do not get the needed object, we should
	 * barf.
	 */
	o = repo_peel_to_type(r, name, len, o, expected_type);
	if (!o)
		return -1;

	oidcpy(oid, &o->oid);
	if (sp[0] == '/') {
		/* "$commit^{/foo}" */
		char *prefix;
		int ret;
		struct commit_list *list = NULL;

		/*
		 * $commit^{/}. Some regex implementation may reject.
		 * We don't need regex anyway. '' pattern always matches.
		 */
		if (sp[1] == '}')
			return 0;

		prefix = xstrndup(sp + 1, name + len - 1 - (sp + 1));
		commit_list_insert((struct commit *)o, &list);
		ret = get_oid_oneline(r, prefix, oid, list);
		free(prefix);
		return ret;
	}
	return 0;
}