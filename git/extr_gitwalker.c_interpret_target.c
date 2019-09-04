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
struct walker {int /*<<< orphan*/  (* fetch_ref ) (struct walker*,struct ref*) ;} ;
struct ref {int /*<<< orphan*/  old_oid; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct ref* alloc_ref (char*) ; 
 int /*<<< orphan*/  check_refname_format (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ref*) ; 
 int /*<<< orphan*/  get_oid_hex (char*,struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct walker*,struct ref*) ; 

__attribute__((used)) static int interpret_target(struct walker *walker, char *target, struct object_id *oid)
{
	if (!get_oid_hex(target, oid))
		return 0;
	if (!check_refname_format(target, 0)) {
		struct ref *ref = alloc_ref(target);
		if (!walker->fetch_ref(walker, ref)) {
			oidcpy(oid, &ref->old_oid);
			free(ref);
			return 0;
		}
		free(ref);
	}
	return -1;
}