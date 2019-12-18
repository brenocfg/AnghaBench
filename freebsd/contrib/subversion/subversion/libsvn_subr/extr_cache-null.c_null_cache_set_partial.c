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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cache__partial_setter_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
null_cache_set_partial(void *cache_void,
                       const void *key,
                       svn_cache__partial_setter_func_t func,
                       void *baton,
                       apr_pool_t *scratch_pool)
{
  /* We know there is nothing to update in this cache. */
  return SVN_NO_ERROR;
}