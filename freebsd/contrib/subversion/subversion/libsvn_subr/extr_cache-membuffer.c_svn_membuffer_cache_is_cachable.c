#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ priority; TYPE_2__* membuffer; } ;
typedef  TYPE_3__ svn_membuffer_cache_t ;
typedef  int svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_4__ {scalar_t__ size; } ;
struct TYPE_5__ {scalar_t__ max_entry_size; TYPE_1__ l2; } ;

/* Variables and functions */
 scalar_t__ MAX_ITEM_SIZE ; 
 scalar_t__ SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY ; 

__attribute__((used)) static svn_boolean_t
svn_membuffer_cache_is_cachable(void *cache_void, apr_size_t size)
{
  /* Don't allow extremely large element sizes. Otherwise, the cache
   * might by thrashed by a few extremely large entries. And the size
   * must be small enough to be stored in a 32 bit value.
   */
  svn_membuffer_cache_t *cache = cache_void;
  return cache->priority > SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY
       ? cache->membuffer->l2.size >= size && MAX_ITEM_SIZE >= size
       : size <= cache->membuffer->max_entry_size;
}