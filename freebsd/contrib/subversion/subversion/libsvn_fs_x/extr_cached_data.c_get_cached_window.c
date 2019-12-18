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
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
struct TYPE_8__ {int chunk_index; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_fs_x__window_cache_key_t ;
struct TYPE_9__ {int /*<<< orphan*/  end_offset; int /*<<< orphan*/ * window; } ;
typedef  TYPE_2__ svn_fs_x__txdelta_cached_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_10__ {int chunk_index; int /*<<< orphan*/  current; int /*<<< orphan*/  window_cache; } ;
typedef  TYPE_3__ rep_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_window_key (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  svn_cache__get (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_cached_window(svn_txdelta_window_t **window_p,
                  rep_state_t *rs,
                  int chunk_index,
                  svn_boolean_t *is_cached,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  /* ask the cache for the desired txdelta window */
  svn_fs_x__txdelta_cached_window_t *cached_window;
  svn_fs_x__window_cache_key_t key = { 0 };
  get_window_key(&key, rs);
  key.chunk_index = chunk_index;
  SVN_ERR(svn_cache__get((void **) &cached_window,
                         is_cached,
                         rs->window_cache,
                         &key,
                         result_pool));

  if (*is_cached)
    {
      /* found it. Pass it back to the caller. */
      *window_p = cached_window->window;

      /* manipulate the RS as if we just read the data */
      rs->current = cached_window->end_offset;
      rs->chunk_index = chunk_index;
    }

  return SVN_NO_ERROR;
}