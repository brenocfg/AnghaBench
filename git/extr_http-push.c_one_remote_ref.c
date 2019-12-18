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
struct ref {struct ref* next; int /*<<< orphan*/  old_oid; } ;
struct object {int dummy; } ;
struct TYPE_2__ {char const* url; scalar_t__ can_update_info_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_fetch_request (struct object*) ; 
 struct ref* alloc_ref (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  free (struct ref*) ; 
 int /*<<< orphan*/  has_object_file (int /*<<< orphan*/ *) ; 
 scalar_t__ http_fetch_ref (char const*,struct ref*) ; 
 struct object* lookup_unknown_object (int /*<<< orphan*/ *) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 struct ref* remote_refs ; 
 TYPE_1__* repo ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void one_remote_ref(const char *refname)
{
	struct ref *ref;
	struct object *obj;

	ref = alloc_ref(refname);

	if (http_fetch_ref(repo->url, ref) != 0) {
		fprintf(stderr,
			"Unable to fetch ref %s from %s\n",
			refname, repo->url);
		free(ref);
		return;
	}

	/*
	 * Fetch a copy of the object if it doesn't exist locally - it
	 * may be required for updating server info later.
	 */
	if (repo->can_update_info_refs && !has_object_file(&ref->old_oid)) {
		obj = lookup_unknown_object(&ref->old_oid);
		fprintf(stderr,	"  fetch %s for %s\n",
			oid_to_hex(&ref->old_oid), refname);
		add_fetch_request(obj);
	}

	ref->next = remote_refs;
	remote_refs = ref;
}