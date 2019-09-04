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
struct blame_origin {int dummy; } ;
struct blame_entry {int num_lines; scalar_t__ s_lno; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_split_if_better (struct blame_scoreboard*,struct blame_entry*,struct blame_entry*) ; 
 int /*<<< orphan*/  decref_split (struct blame_entry*) ; 
 int /*<<< orphan*/  split_overlap (struct blame_entry*,struct blame_entry*,int,int,int,struct blame_origin*) ; 

__attribute__((used)) static void handle_split(struct blame_scoreboard *sb,
			 struct blame_entry *ent,
			 int tlno, int plno, int same,
			 struct blame_origin *parent,
			 struct blame_entry *split)
{
	if (ent->num_lines <= tlno)
		return;
	if (tlno < same) {
		struct blame_entry potential[3];
		tlno += ent->s_lno;
		same += ent->s_lno;
		split_overlap(potential, ent, tlno, plno, same, parent);
		copy_split_if_better(sb, split, potential);
		decref_split(potential);
	}
}