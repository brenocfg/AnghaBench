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
struct ref {int /*<<< orphan*/  old_oid; int /*<<< orphan*/  name; struct ref* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPDATE_REFS_DIE_ON_ERR ; 
 scalar_t__ ends_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  has_object_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  starts_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  update_ref (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_followtags(const struct ref *refs, const char *msg)
{
	const struct ref *ref;
	for (ref = refs; ref; ref = ref->next) {
		if (!starts_with(ref->name, "refs/tags/"))
			continue;
		if (ends_with(ref->name, "^{}"))
			continue;
		if (!has_object_file(&ref->old_oid))
			continue;
		update_ref(msg, ref->name, &ref->old_oid, NULL, 0,
			   UPDATE_REFS_DIE_ON_ERR);
	}
}