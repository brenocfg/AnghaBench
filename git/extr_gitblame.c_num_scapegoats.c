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
struct rev_info {int dummy; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int commit_list_count (struct commit_list*) ; 
 struct commit_list* first_scapegoat (struct rev_info*,struct commit*,int) ; 

__attribute__((used)) static int num_scapegoats(struct rev_info *revs, struct commit *commit, int reverse)
{
	struct commit_list *l = first_scapegoat(revs, commit, reverse);
	return commit_list_count(l);
}