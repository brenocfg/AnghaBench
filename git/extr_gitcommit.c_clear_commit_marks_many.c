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
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_commit_marks_1 (struct commit_list**,struct commit*,unsigned int) ; 
 struct commit* pop_commit (struct commit_list**) ; 

void clear_commit_marks_many(int nr, struct commit **commit, unsigned int mark)
{
	struct commit_list *list = NULL;

	while (nr--) {
		clear_commit_marks_1(&list, *commit, mark);
		commit++;
	}
	while (list)
		clear_commit_marks_1(&list, pop_commit(&list), mark);
}