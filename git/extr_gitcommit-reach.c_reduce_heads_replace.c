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

/* Variables and functions */
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* reduce_heads (struct commit_list*) ; 

void reduce_heads_replace(struct commit_list **heads)
{
	struct commit_list *result = reduce_heads(*heads);
	free_commit_list(*heads);
	*heads = result;
}