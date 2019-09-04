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
struct ref {int /*<<< orphan*/  new_oid; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct ref* alloc_delete_ref () ; 
 struct ref* alloc_ref (char const*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 

__attribute__((used)) static int try_explicit_object_name(const char *name,
				    struct ref **match)
{
	struct object_id oid;

	if (!*name) {
		if (match)
			*match = alloc_delete_ref();
		return 0;
	}

	if (get_oid(name, &oid))
		return -1;

	if (match) {
		*match = alloc_ref(name);
		oidcpy(&(*match)->new_oid, &oid);
	}
	return 0;
}