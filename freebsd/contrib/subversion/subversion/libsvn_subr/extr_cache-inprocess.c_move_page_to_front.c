#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct cache_page {int /*<<< orphan*/  next; } ;
struct TYPE_4__ {struct cache_page* sentinel; } ;
typedef  TYPE_1__ inprocess_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  insert_page (TYPE_1__*,struct cache_page*) ; 
 int /*<<< orphan*/  remove_page_from_list (struct cache_page*) ; 

__attribute__((used)) static svn_error_t *
move_page_to_front(inprocess_cache_t *cache,
                   struct cache_page *page)
{
  /* This function is called whilst CACHE is locked. */

  SVN_ERR_ASSERT(page != cache->sentinel);

  if (! page->next)
    return SVN_NO_ERROR;

  remove_page_from_list(page);
  insert_page(cache, page);

  return SVN_NO_ERROR;
}