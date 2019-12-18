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
struct commit_name {int prio; int /*<<< orphan*/ * path; int /*<<< orphan*/  oid; scalar_t__ name_checked; struct tag* tag; int /*<<< orphan*/  entry; int /*<<< orphan*/  peeled; } ;

/* Variables and functions */
 struct commit_name* find_commit_name (struct object_id const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  names ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 int /*<<< orphan*/  oidhash (struct object_id const*) ; 
 scalar_t__ replace_name (struct commit_name*,int,struct object_id const*,struct tag**) ; 
 struct commit_name* xmalloc (int) ; 
 int /*<<< orphan*/ * xstrdup (char const*) ; 

__attribute__((used)) static void add_to_known_names(const char *path,
			       const struct object_id *peeled,
			       int prio,
			       const struct object_id *oid)
{
	struct commit_name *e = find_commit_name(peeled);
	struct tag *tag = NULL;
	if (replace_name(e, prio, oid, &tag)) {
		if (!e) {
			e = xmalloc(sizeof(struct commit_name));
			oidcpy(&e->peeled, peeled);
			hashmap_entry_init(&e->entry, oidhash(peeled));
			hashmap_add(&names, &e->entry);
			e->path = NULL;
		}
		e->tag = tag;
		e->prio = prio;
		e->name_checked = 0;
		oidcpy(&e->oid, oid);
		free(e->path);
		e->path = xstrdup(path);
	}
}