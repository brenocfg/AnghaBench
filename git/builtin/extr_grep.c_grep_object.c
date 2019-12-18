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
struct tree_desc {int dummy; } ;
struct strbuf {int /*<<< orphan*/  len; } ;
struct pathspec {int dummy; } ;
struct object {scalar_t__ type; int /*<<< orphan*/  oid; } ;
struct grep_opt {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 scalar_t__ OBJ_BLOB ; 
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TREE ; 
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int grep_oid (struct grep_opt*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  grep_read_lock () ; 
 int /*<<< orphan*/  grep_read_unlock () ; 
 int grep_tree (struct grep_opt*,struct pathspec const*,struct tree_desc*,struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,void*,unsigned long) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 void* read_object_with_reference (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  tree_type ; 
 int /*<<< orphan*/  type_name (scalar_t__) ; 

__attribute__((used)) static int grep_object(struct grep_opt *opt, const struct pathspec *pathspec,
		       struct object *obj, const char *name, const char *path)
{
	if (obj->type == OBJ_BLOB)
		return grep_oid(opt, &obj->oid, name, 0, path);
	if (obj->type == OBJ_COMMIT || obj->type == OBJ_TREE) {
		struct tree_desc tree;
		void *data;
		unsigned long size;
		struct strbuf base;
		int hit, len;

		grep_read_lock();
		data = read_object_with_reference(opt->repo,
						  &obj->oid, tree_type,
						  &size, NULL);
		grep_read_unlock();

		if (!data)
			die(_("unable to read tree (%s)"), oid_to_hex(&obj->oid));

		len = name ? strlen(name) : 0;
		strbuf_init(&base, PATH_MAX + len + 1);
		if (len) {
			strbuf_add(&base, name, len);
			strbuf_addch(&base, ':');
		}
		init_tree_desc(&tree, data, size);
		hit = grep_tree(opt, pathspec, &tree, &base, base.len,
				obj->type == OBJ_COMMIT);
		strbuf_release(&base);
		free(data);
		return hit;
	}
	die(_("unable to grep from object of type %s"), type_name(obj->type));
}