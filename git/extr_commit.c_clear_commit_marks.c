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
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_commit_marks_many (int,struct commit**,unsigned int) ; 

void clear_commit_marks(struct commit *commit, unsigned int mark)
{
	clear_commit_marks_many(1, &commit, mark);
}