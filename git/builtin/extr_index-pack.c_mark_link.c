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
struct object {int type; int /*<<< orphan*/  flags; int /*<<< orphan*/  oid; } ;
struct fsck_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_LINK ; 
 int OBJ_ANY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mark_link(struct object *obj, int type, void *data, struct fsck_options *options)
{
	if (!obj)
		return -1;

	if (type != OBJ_ANY && obj->type != type)
		die(_("object type mismatch at %s"), oid_to_hex(&obj->oid));

	obj->flags |= FLAG_LINK;
	return 0;
}