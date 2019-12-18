#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ group_count; scalar_t__ spare_group_count; unsigned char* group_initialized; TYPE_1__* directory; } ;
typedef  TYPE_2__ svn_membuffer_t ;
struct TYPE_7__ {int chain_length; void* previous; void* next; scalar_t__ used; } ;
typedef  TYPE_3__ group_header_t ;
typedef  scalar_t__ apr_uint32_t ;
struct TYPE_5__ {TYPE_3__ header; } ;

/* Variables and functions */
 scalar_t__ GROUP_INIT_GRANULARITY ; 
 void* NO_INDEX ; 

__attribute__((used)) static void
initialize_group(svn_membuffer_t *cache, apr_uint32_t group_index)
{
  unsigned char bit_mask;
  apr_uint32_t i;

  /* range of groups to initialize due to GROUP_INIT_GRANULARITY */
  apr_uint32_t first_index =
      (group_index / GROUP_INIT_GRANULARITY) * GROUP_INIT_GRANULARITY;
  apr_uint32_t last_index = first_index + GROUP_INIT_GRANULARITY;
  if (last_index > cache->group_count + cache->spare_group_count)
    last_index = cache->group_count + cache->spare_group_count;

  for (i = first_index; i < last_index; ++i)
    {
      group_header_t *header = &cache->directory[i].header;
      header->used = 0;
      header->chain_length = 1;
      header->next = NO_INDEX;
      header->previous = NO_INDEX;
    }

  /* set the "initialized" bit for these groups */
  bit_mask
    = (unsigned char)(1 << ((group_index / GROUP_INIT_GRANULARITY) % 8));
  cache->group_initialized[group_index / (8 * GROUP_INIT_GRANULARITY)]
    |= bit_mask;
}