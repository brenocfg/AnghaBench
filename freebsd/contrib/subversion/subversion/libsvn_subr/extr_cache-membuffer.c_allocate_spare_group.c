#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t first_spare_group; scalar_t__ max_spare_used; scalar_t__ spare_group_count; size_t group_count; TYPE_3__* directory; } ;
typedef  TYPE_2__ svn_membuffer_t ;
struct TYPE_8__ {size_t next; int /*<<< orphan*/  used; } ;
struct TYPE_10__ {TYPE_1__ header; } ;
typedef  TYPE_3__ entry_group_t ;
typedef  size_t apr_uint32_t ;

/* Variables and functions */
 size_t NO_INDEX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  initialize_group (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  is_group_initialized (TYPE_2__*,size_t) ; 

__attribute__((used)) static entry_group_t *
allocate_spare_group(svn_membuffer_t *cache)
{
  entry_group_t *group = NULL;

  /* is there some ready-to-use group? */
  if (cache->first_spare_group != NO_INDEX)
    {
      group = &cache->directory[cache->first_spare_group];
      cache->first_spare_group = group->header.next;
    }

  /* any so far untouched spares available? */
  else if (cache->max_spare_used < cache->spare_group_count)
    {
      apr_uint32_t group_index = cache->group_count + cache->max_spare_used;
      ++cache->max_spare_used;

      if (!is_group_initialized(cache, group_index))
        initialize_group(cache, group_index);

      group = &cache->directory[group_index];
    }

  /* spare groups must be empty */
  assert(!group || !group->header.used);
  return group;
}