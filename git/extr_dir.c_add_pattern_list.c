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
struct pattern_list {char const* src; } ;
struct exclude_list_group {scalar_t__ nr; struct pattern_list* pl; int /*<<< orphan*/  alloc; } ;
struct dir_struct {struct exclude_list_group* exclude_list_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct pattern_list*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pattern_list*,int /*<<< orphan*/ ,int) ; 

struct pattern_list *add_pattern_list(struct dir_struct *dir,
				      int group_type, const char *src)
{
	struct pattern_list *pl;
	struct exclude_list_group *group;

	group = &dir->exclude_list_group[group_type];
	ALLOC_GROW(group->pl, group->nr + 1, group->alloc);
	pl = &group->pl[group->nr++];
	memset(pl, 0, sizeof(*pl));
	pl->src = src;
	return pl;
}