#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  window_sizes_t ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_fs_x__window_cache_key_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  window_cache; } ;
typedef  TYPE_2__ rep_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_cached_window_sizes_func ; 
 int /*<<< orphan*/  get_window_key (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_cached_window_sizes(window_sizes_t **sizes,
                        rep_state_t *rs,
                        svn_boolean_t *is_cached,
                        apr_pool_t *pool)
{
  svn_fs_x__window_cache_key_t key = { 0 };
  SVN_ERR(svn_cache__get_partial((void **)sizes,
                                 is_cached,
                                 rs->window_cache,
                                 get_window_key(&key, rs),
                                 get_cached_window_sizes_func,
                                 NULL,
                                 pool));

  return SVN_NO_ERROR;
}