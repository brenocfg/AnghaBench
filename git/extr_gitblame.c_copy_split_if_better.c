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
struct blame_scoreboard {int dummy; } ;
struct blame_entry {scalar_t__ suspect; } ;

/* Variables and functions */
 scalar_t__ blame_entry_score (struct blame_scoreboard*,struct blame_entry*) ; 
 int /*<<< orphan*/  blame_origin_incref (scalar_t__) ; 
 int /*<<< orphan*/  decref_split (struct blame_entry*) ; 
 int /*<<< orphan*/  memcpy (struct blame_entry*,struct blame_entry*,int) ; 

__attribute__((used)) static void copy_split_if_better(struct blame_scoreboard *sb,
				 struct blame_entry *best_so_far,
				 struct blame_entry *potential)
{
	int i;

	if (!potential[1].suspect)
		return;
	if (best_so_far[1].suspect) {
		if (blame_entry_score(sb, &potential[1]) <
		    blame_entry_score(sb, &best_so_far[1]))
			return;
	}

	for (i = 0; i < 3; i++)
		blame_origin_incref(potential[i].suspect);
	decref_split(best_so_far);
	memcpy(best_so_far, potential, sizeof(struct blame_entry[3]));
}