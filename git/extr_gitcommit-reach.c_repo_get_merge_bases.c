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
struct repository {int dummy; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 struct commit_list* get_merge_bases_many_0 (struct repository*,struct commit*,int,struct commit**,int) ; 

struct commit_list *repo_get_merge_bases(struct repository *r,
					 struct commit *one,
					 struct commit *two)
{
	return get_merge_bases_many_0(r, one, 1, &two, 1);
}