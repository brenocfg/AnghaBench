#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ timestamp_t ;
struct fetch_pack_args {int dummy; } ;
struct TYPE_7__ {TYPE_2__* item; } ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {scalar_t__ date; TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLETE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_3__* complete ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pop_most_recent_commit (TYPE_3__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_verbose (struct fetch_pack_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_recent_complete_commits(struct fetch_pack_args *args,
					 timestamp_t cutoff)
{
	while (complete && cutoff <= complete->item->date) {
		print_verbose(args, _("Marking %s as complete"),
			      oid_to_hex(&complete->item->object.oid));
		pop_most_recent_commit(&complete, COMPLETE);
	}
}