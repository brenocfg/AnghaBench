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
struct blame_scoreboard {int /*<<< orphan*/  ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  compare_blame_final ; 
 int /*<<< orphan*/  get_next_blame ; 
 int /*<<< orphan*/  llist_mergesort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_next_blame ; 

void blame_sort_final(struct blame_scoreboard *sb)
{
	sb->ent = llist_mergesort(sb->ent, get_next_blame, set_next_blame,
				  compare_blame_final);
}