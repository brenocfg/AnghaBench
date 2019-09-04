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
struct exclude_list_group {scalar_t__ nr; struct exclude_list* el; int /*<<< orphan*/  alloc; } ;
struct exclude_list {char const* src; } ;
struct dir_struct {struct exclude_list_group* exclude_list_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct exclude_list*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct exclude_list*,int /*<<< orphan*/ ,int) ; 

struct exclude_list *add_exclude_list(struct dir_struct *dir,
				      int group_type, const char *src)
{
	struct exclude_list *el;
	struct exclude_list_group *group;

	group = &dir->exclude_list_group[group_type];
	ALLOC_GROW(group->el, group->nr + 1, group->alloc);
	el = &group->el[group->nr++];
	memset(el, 0, sizeof(*el));
	el->src = src;
	return el;
}