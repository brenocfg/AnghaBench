#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t flags; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 size_t GIT_INDEX_ENTRY_NAMEMASK ; 

__attribute__((used)) static void index_entry_adjust_namemask(
		git_index_entry *entry,
		size_t path_length)
{
	entry->flags &= ~GIT_INDEX_ENTRY_NAMEMASK;

	if (path_length < GIT_INDEX_ENTRY_NAMEMASK)
		entry->flags |= path_length & GIT_INDEX_ENTRY_NAMEMASK;
	else
		entry->flags |= GIT_INDEX_ENTRY_NAMEMASK;
}