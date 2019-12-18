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
struct blame_scoreboard {int /*<<< orphan*/  copy_score; int /*<<< orphan*/  move_score; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLAME_DEFAULT_COPY_SCORE ; 
 int /*<<< orphan*/  BLAME_DEFAULT_MOVE_SCORE ; 
 int /*<<< orphan*/  memset (struct blame_scoreboard*,int /*<<< orphan*/ ,int) ; 

void init_scoreboard(struct blame_scoreboard *sb)
{
	memset(sb, 0, sizeof(struct blame_scoreboard));
	sb->move_score = BLAME_DEFAULT_MOVE_SCORE;
	sb->copy_score = BLAME_DEFAULT_COPY_SCORE;
}