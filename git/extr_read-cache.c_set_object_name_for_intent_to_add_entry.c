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
struct cache_entry {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  blob_type ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 scalar_t__ write_object_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 

void set_object_name_for_intent_to_add_entry(struct cache_entry *ce)
{
	struct object_id oid;
	if (write_object_file("", 0, blob_type, &oid))
		die(_("cannot create an empty blob in the object database"));
	oidcpy(&ce->oid, &oid);
}