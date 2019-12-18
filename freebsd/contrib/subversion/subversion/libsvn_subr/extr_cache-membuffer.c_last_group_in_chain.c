#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* directory; } ;
typedef  TYPE_2__ svn_membuffer_t ;
struct TYPE_7__ {size_t next; } ;
struct TYPE_9__ {TYPE_1__ header; } ;
typedef  TYPE_3__ entry_group_t ;

/* Variables and functions */
 size_t NO_INDEX ; 

__attribute__((used)) static entry_group_t *
last_group_in_chain(svn_membuffer_t *cache,
                    entry_group_t *group)
{
  while (group->header.next != NO_INDEX)
    group = &cache->directory[group->header.next];

  return group;
}