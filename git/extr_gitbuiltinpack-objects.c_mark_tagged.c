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
struct object_id {int /*<<< orphan*/  hash; } ;
struct object_entry {int tagged; } ;

/* Variables and functions */
 struct object_entry* packlist_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peel_ref (char const*,struct object_id*) ; 
 int /*<<< orphan*/  to_pack ; 

__attribute__((used)) static int mark_tagged(const char *path, const struct object_id *oid, int flag,
		       void *cb_data)
{
	struct object_id peeled;
	struct object_entry *entry = packlist_find(&to_pack, oid->hash, NULL);

	if (entry)
		entry->tagged = 1;
	if (!peel_ref(path, &peeled)) {
		entry = packlist_find(&to_pack, peeled.hash, NULL);
		if (entry)
			entry->tagged = 1;
	}
	return 0;
}