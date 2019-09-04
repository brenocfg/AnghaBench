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
struct blame_entry {struct blame_entry* next; } ;

/* Variables and functions */
 unsigned int blame_entry_score (struct blame_scoreboard*,struct blame_entry*) ; 

__attribute__((used)) static struct blame_entry **filter_small(struct blame_scoreboard *sb,
					 struct blame_entry **small,
					 struct blame_entry **source,
					 unsigned score_min)
{
	struct blame_entry *p = *source;
	struct blame_entry *oldsmall = *small;
	while (p) {
		if (blame_entry_score(sb, p) <= score_min) {
			*small = p;
			small = &p->next;
			p = *small;
		} else {
			*source = p;
			source = &p->next;
			p = *source;
		}
	}
	*small = oldsmall;
	*source = NULL;
	return small;
}