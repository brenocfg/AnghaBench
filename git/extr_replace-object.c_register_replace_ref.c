#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct repository {TYPE_1__* objects; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct replace_object {int /*<<< orphan*/  replacement; TYPE_2__ original; } ;
struct object_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  replace_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (struct replace_object*) ; 
 scalar_t__ get_oid_hex (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 scalar_t__ oidmap_put (int /*<<< orphan*/ ,struct replace_object*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 
 struct replace_object* xmalloc (int) ; 

__attribute__((used)) static int register_replace_ref(struct repository *r,
				const char *refname,
				const struct object_id *oid,
				int flag, void *cb_data)
{
	/* Get sha1 from refname */
	const char *slash = strrchr(refname, '/');
	const char *hash = slash ? slash + 1 : refname;
	struct replace_object *repl_obj = xmalloc(sizeof(*repl_obj));

	if (get_oid_hex(hash, &repl_obj->original.oid)) {
		free(repl_obj);
		warning(_("bad replace ref name: %s"), refname);
		return 0;
	}

	/* Copy sha1 from the read ref */
	oidcpy(&repl_obj->replacement, oid);

	/* Register new object */
	if (oidmap_put(r->objects->replace_map, repl_obj))
		die(_("duplicate replace ref: %s"), refname);

	return 0;
}