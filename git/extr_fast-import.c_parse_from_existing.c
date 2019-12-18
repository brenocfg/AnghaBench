#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* versions; } ;
struct branch {int /*<<< orphan*/  oid; TYPE_1__ branch_tree; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit_type ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_from_commit (struct branch*,char*,unsigned long) ; 
 char* read_object_with_reference (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void parse_from_existing(struct branch *b)
{
	if (is_null_oid(&b->oid)) {
		oidclr(&b->branch_tree.versions[0].oid);
		oidclr(&b->branch_tree.versions[1].oid);
	} else {
		unsigned long size;
		char *buf;

		buf = read_object_with_reference(the_repository,
						 &b->oid, commit_type, &size,
						 &b->oid);
		parse_from_commit(b, buf, size);
		free(buf);
	}
}