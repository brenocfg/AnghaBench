#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_boolean_t ;
struct TYPE_2__ {int items_per_page; } ;
typedef  TYPE_1__ inprocess_cache_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int SVN_ALLOCATOR_RECOMMENDED_MAX_FREE ; 

__attribute__((used)) static svn_boolean_t
inprocess_cache_is_cachable(void *cache_void, apr_size_t size)
{
  /* Be relatively strict: per page we should not allocate more than
   * we could spare as "unused" memory.
   * But in most cases, nobody will ask anyway. And in no case, this
   * will be used for checks _inside_ the cache code.
   */
  inprocess_cache_t *cache = cache_void;
  return size < SVN_ALLOCATOR_RECOMMENDED_MAX_FREE / cache->items_per_page;
}