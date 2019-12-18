#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ push_remote; scalar_t__ push; } ;
struct TYPE_8__ {char const* color; char* head; TYPE_1__ remote_ref; } ;
struct used_atom {char* name; scalar_t__ source; TYPE_2__ u; } ;
struct tag {int dummy; } ;
struct strbuf {int dummy; } ;
struct ref_array_item {int flag; char const* refname; scalar_t__ kind; int /*<<< orphan*/  objectname; struct atom_value* value; void* symref; } ;
struct object_info {int dummy; } ;
struct object {scalar_t__ type; } ;
struct branch {int dummy; } ;
struct atom_value {int /*<<< orphan*/ * s; int /*<<< orphan*/  handler; struct used_atom* atom; } ;
typedef  int /*<<< orphan*/  empty ;
struct TYPE_10__ {int /*<<< orphan*/ * contentp; } ;
struct TYPE_9__ {int /*<<< orphan*/  oid; TYPE_5__ info; int /*<<< orphan*/  content; } ;

/* Variables and functions */
 scalar_t__ FILTER_REFS_BRANCHES ; 
 struct object_info OBJECT_INFO_INIT ; 
 scalar_t__ OBJ_TAG ; 
 int REF_ISPACKED ; 
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 scalar_t__ SOURCE_NONE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  align_atom_handler ; 
 int /*<<< orphan*/  append_atom ; 
 struct branch* branch_get (char const*) ; 
 char* branch_get_push (struct branch*,int /*<<< orphan*/ *) ; 
 char* branch_get_upstream (struct branch*,int /*<<< orphan*/ *) ; 
 char* copy_advance (char*,char*) ; 
 int /*<<< orphan*/  else_atom_handler ; 
 int /*<<< orphan*/  end_atom_handler ; 
 int /*<<< orphan*/  fill_remote_ref_details (struct used_atom*,char const*,struct branch*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_object (struct ref_array_item*,int,struct object**,TYPE_3__*,struct strbuf*) ; 
 char* get_refname (struct used_atom*,struct ref_array_item*) ; 
 char* get_symref (struct used_atom*,struct ref_array_item*) ; 
 int /*<<< orphan*/ * get_tagged_oid (struct tag*) ; 
 int /*<<< orphan*/ * get_worktree_path (struct used_atom*,struct ref_array_item*) ; 
 scalar_t__ grab_objectname (char const*,int /*<<< orphan*/ *,struct atom_value*,struct used_atom*) ; 
 int /*<<< orphan*/  if_atom_handler ; 
 int /*<<< orphan*/  memcmp (TYPE_5__*,struct object_info*,int) ; 
 scalar_t__ need_symref ; 
 scalar_t__ need_tagged ; 
 TYPE_3__ oi ; 
 TYPE_3__ oi_deref ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 void* resolve_refdup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int strbuf_addf_ret (struct strbuf*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  then_atom_handler ; 
 struct used_atom* used_atom ; 
 int used_atom_cnt ; 
 struct atom_value* xcalloc (int,int) ; 
 void* xstrdup (char const*) ; 
 int /*<<< orphan*/ * xstrfmt (char*,char const*) ; 

__attribute__((used)) static int populate_value(struct ref_array_item *ref, struct strbuf *err)
{
	struct object *obj;
	int i;
	struct object_info empty = OBJECT_INFO_INIT;

	ref->value = xcalloc(used_atom_cnt, sizeof(struct atom_value));

	if (need_symref && (ref->flag & REF_ISSYMREF) && !ref->symref) {
		ref->symref = resolve_refdup(ref->refname, RESOLVE_REF_READING,
					     NULL, NULL);
		if (!ref->symref)
			ref->symref = xstrdup("");
	}

	/* Fill in specials first */
	for (i = 0; i < used_atom_cnt; i++) {
		struct used_atom *atom = &used_atom[i];
		const char *name = used_atom[i].name;
		struct atom_value *v = &ref->value[i];
		int deref = 0;
		const char *refname;
		struct branch *branch = NULL;

		v->handler = append_atom;
		v->atom = atom;

		if (*name == '*') {
			deref = 1;
			name++;
		}

		if (starts_with(name, "refname"))
			refname = get_refname(atom, ref);
		else if (!strcmp(name, "worktreepath")) {
			if (ref->kind == FILTER_REFS_BRANCHES)
				v->s = get_worktree_path(atom, ref);
			else
				v->s = xstrdup("");
			continue;
		}
		else if (starts_with(name, "symref"))
			refname = get_symref(atom, ref);
		else if (starts_with(name, "upstream")) {
			const char *branch_name;
			/* only local branches may have an upstream */
			if (!skip_prefix(ref->refname, "refs/heads/",
					 &branch_name)) {
				v->s = xstrdup("");
				continue;
			}
			branch = branch_get(branch_name);

			refname = branch_get_upstream(branch, NULL);
			if (refname)
				fill_remote_ref_details(atom, refname, branch, &v->s);
			else
				v->s = xstrdup("");
			continue;
		} else if (atom->u.remote_ref.push) {
			const char *branch_name;
			v->s = xstrdup("");
			if (!skip_prefix(ref->refname, "refs/heads/",
					 &branch_name))
				continue;
			branch = branch_get(branch_name);

			if (atom->u.remote_ref.push_remote)
				refname = NULL;
			else {
				refname = branch_get_push(branch, NULL);
				if (!refname)
					continue;
			}
			/* We will definitely re-init v->s on the next line. */
			free((char *)v->s);
			fill_remote_ref_details(atom, refname, branch, &v->s);
			continue;
		} else if (starts_with(name, "color:")) {
			v->s = xstrdup(atom->u.color);
			continue;
		} else if (!strcmp(name, "flag")) {
			char buf[256], *cp = buf;
			if (ref->flag & REF_ISSYMREF)
				cp = copy_advance(cp, ",symref");
			if (ref->flag & REF_ISPACKED)
				cp = copy_advance(cp, ",packed");
			if (cp == buf)
				v->s = xstrdup("");
			else {
				*cp = '\0';
				v->s = xstrdup(buf + 1);
			}
			continue;
		} else if (!deref && grab_objectname(name, &ref->objectname, v, atom)) {
			continue;
		} else if (!strcmp(name, "HEAD")) {
			if (atom->u.head && !strcmp(ref->refname, atom->u.head))
				v->s = xstrdup("*");
			else
				v->s = xstrdup(" ");
			continue;
		} else if (starts_with(name, "align")) {
			v->handler = align_atom_handler;
			v->s = xstrdup("");
			continue;
		} else if (!strcmp(name, "end")) {
			v->handler = end_atom_handler;
			v->s = xstrdup("");
			continue;
		} else if (starts_with(name, "if")) {
			const char *s;
			if (skip_prefix(name, "if:", &s))
				v->s = xstrdup(s);
			else
				v->s = xstrdup("");
			v->handler = if_atom_handler;
			continue;
		} else if (!strcmp(name, "then")) {
			v->handler = then_atom_handler;
			v->s = xstrdup("");
			continue;
		} else if (!strcmp(name, "else")) {
			v->handler = else_atom_handler;
			v->s = xstrdup("");
			continue;
		} else
			continue;

		if (!deref)
			v->s = xstrdup(refname);
		else
			v->s = xstrfmt("%s^{}", refname);
		free((char *)refname);
	}

	for (i = 0; i < used_atom_cnt; i++) {
		struct atom_value *v = &ref->value[i];
		if (v->s == NULL && used_atom[i].source == SOURCE_NONE)
			return strbuf_addf_ret(err, -1, _("missing object %s for %s"),
					       oid_to_hex(&ref->objectname), ref->refname);
	}

	if (need_tagged)
		oi.info.contentp = &oi.content;
	if (!memcmp(&oi.info, &empty, sizeof(empty)) &&
	    !memcmp(&oi_deref.info, &empty, sizeof(empty)))
		return 0;


	oi.oid = ref->objectname;
	if (get_object(ref, 0, &obj, &oi, err))
		return -1;

	/*
	 * If there is no atom that wants to know about tagged
	 * object, we are done.
	 */
	if (!need_tagged || (obj->type != OBJ_TAG))
		return 0;

	/*
	 * If it is a tag object, see if we use a value that derefs
	 * the object, and if we do grab the object it refers to.
	 */
	oi_deref.oid = *get_tagged_oid((struct tag *)obj);

	/*
	 * NEEDSWORK: This derefs tag only once, which
	 * is good to deal with chains of trust, but
	 * is not consistent with what deref_tag() does
	 * which peels the onion to the core.
	 */
	return get_object(ref, 1, &obj, &oi_deref, err);
}