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
typedef  int /*<<< orphan*/  svn_iter_apr_hash_cb_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static svn_error_t *
null_cache_iter(svn_boolean_t *completed,
                void *cache_void,
                svn_iter_apr_hash_cb_t user_cb,
                void *user_baton,
                apr_pool_t *scratch_pool)
{
  /* Iteration over an empty set is a no-op. */
  if (completed)
    *completed = TRUE;

  return SVN_NO_ERROR;
}