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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_tag_chain (struct object_id const*) ; 
 scalar_t__ packlist_find (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  peel_ref (char const*,struct object_id*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  to_pack ; 

__attribute__((used)) static int add_ref_tag(const char *path, const struct object_id *oid, int flag, void *cb_data)
{
	struct object_id peeled;

	if (starts_with(path, "refs/tags/") && /* is a tag? */
	    !peel_ref(path, &peeled)    && /* peelable? */
	    packlist_find(&to_pack, &peeled))      /* object packed? */
		add_tag_chain(oid);
	return 0;
}