#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct blame_scoreboard {int /*<<< orphan*/  (* on_sanity_fail ) (struct blame_scoreboard*,int) ;struct blame_entry* ent; } ;
struct blame_entry {TYPE_3__* suspect; struct blame_entry* next; } ;
struct TYPE_6__ {scalar_t__ refcnt; char* path; TYPE_2__* commit; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct TYPE_5__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,scalar_t__) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct blame_scoreboard*,int) ; 

__attribute__((used)) static void sanity_check_refcnt(struct blame_scoreboard *sb)
{
	int baa = 0;
	struct blame_entry *ent;

	for (ent = sb->ent; ent; ent = ent->next) {
		/* Nobody should have zero or negative refcnt */
		if (ent->suspect->refcnt <= 0) {
			fprintf(stderr, "%s in %s has negative refcnt %d\n",
				ent->suspect->path,
				oid_to_hex(&ent->suspect->commit->object.oid),
				ent->suspect->refcnt);
			baa = 1;
		}
	}
	if (baa)
		sb->on_sanity_fail(sb, baa);
}