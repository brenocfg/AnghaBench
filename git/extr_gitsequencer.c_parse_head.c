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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 struct commit* lookup_commit_reference (struct repository*,struct object_id*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oideq (struct object_id*,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_head(struct repository *r, struct commit **head)
{
	struct commit *current_head;
	struct object_id oid;

	if (get_oid("HEAD", &oid)) {
		current_head = NULL;
	} else {
		current_head = lookup_commit_reference(r, &oid);
		if (!current_head)
			return error(_("could not parse HEAD"));
		if (!oideq(&oid, &current_head->object.oid)) {
			warning(_("HEAD %s is not a commit!"),
				oid_to_hex(&oid));
		}
		if (parse_commit(current_head))
			return error(_("could not parse HEAD commit"));
	}
	*head = current_head;

	return 0;
}