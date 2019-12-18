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
struct TYPE_4__ {int flags; } ;
struct commit {TYPE_2__ object; } ;
struct blame_scoreboard {struct blame_entry* ent; } ;
struct blame_origin {scalar_t__ guilty; struct blame_origin* next; } ;
struct blame_entry {struct blame_entry* next; TYPE_1__* suspect; } ;
struct TYPE_3__ {struct commit* commit; } ;

/* Variables and functions */
 int MORE_THAN_ONE_PATH ; 
 int OUTPUT_PORCELAIN ; 
 int /*<<< orphan*/  emit_other (struct blame_scoreboard*,struct blame_entry*,int) ; 
 int /*<<< orphan*/  emit_porcelain (struct blame_scoreboard*,struct blame_entry*,int) ; 
 struct blame_origin* get_blame_suspects (struct commit*) ; 

__attribute__((used)) static void output(struct blame_scoreboard *sb, int option)
{
	struct blame_entry *ent;

	if (option & OUTPUT_PORCELAIN) {
		for (ent = sb->ent; ent; ent = ent->next) {
			int count = 0;
			struct blame_origin *suspect;
			struct commit *commit = ent->suspect->commit;
			if (commit->object.flags & MORE_THAN_ONE_PATH)
				continue;
			for (suspect = get_blame_suspects(commit); suspect; suspect = suspect->next) {
				if (suspect->guilty && count++) {
					commit->object.flags |= MORE_THAN_ONE_PATH;
					break;
				}
			}
		}
	}

	for (ent = sb->ent; ent; ent = ent->next) {
		if (option & OUTPUT_PORCELAIN)
			emit_porcelain(sb, ent, option);
		else {
			emit_other(sb, ent, option);
		}
	}
}