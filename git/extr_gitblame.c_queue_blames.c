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
struct blame_scoreboard {int /*<<< orphan*/  commits; } ;
struct blame_origin {int /*<<< orphan*/  commit; struct blame_entry* suspects; struct blame_origin* next; } ;
struct blame_entry {int dummy; } ;

/* Variables and functions */
 struct blame_entry* blame_merge (struct blame_entry*,struct blame_entry*) ; 
 struct blame_origin* get_blame_suspects (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prio_queue_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void queue_blames(struct blame_scoreboard *sb, struct blame_origin *porigin,
			 struct blame_entry *sorted)
{
	if (porigin->suspects)
		porigin->suspects = blame_merge(porigin->suspects, sorted);
	else {
		struct blame_origin *o;
		for (o = get_blame_suspects(porigin->commit); o; o = o->next) {
			if (o->suspects) {
				porigin->suspects = sorted;
				return;
			}
		}
		porigin->suspects = sorted;
		prio_queue_put(&sb->commits, porigin->commit);
	}
}