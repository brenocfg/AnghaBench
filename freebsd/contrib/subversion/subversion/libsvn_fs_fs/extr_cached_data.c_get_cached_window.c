#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int chunk_index; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ window_cache_key_t ;
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
struct TYPE_12__ {int /*<<< orphan*/  end_offset; int /*<<< orphan*/ * window; } ;
typedef  TYPE_2__ svn_fs_fs__txdelta_cached_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_13__ {int chunk_index; int /*<<< orphan*/  current; int /*<<< orphan*/  window_cache; int /*<<< orphan*/  raw_window_cache; } ;
typedef  TYPE_3__ rep_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_window_key (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  parse_raw_window ; 
 int /*<<< orphan*/  svn_cache__get (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_cached_window(svn_txdelta_window_t **window_p,
                  rep_state_t *rs,
                  int chunk_index,
                  svn_boolean_t *is_cached,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  if (! rs->window_cache)
    {
      /* txdelta window has not been enabled */
      *is_cached = FALSE;
    }
  else
    {
      /* ask the cache for the desired txdelta window */
      svn_fs_fs__txdelta_cached_window_t *cached_window;
      window_cache_key_t key = { 0 };
      get_window_key(&key, rs);
      key.chunk_index = chunk_index;
      SVN_ERR(svn_cache__get((void **) &cached_window,
                             is_cached,
                             rs->window_cache,
                             &key,
                             result_pool));

      /* If we did not find a parsed txdelta window, we might have a raw
         version of it in our cache.  If so, read, parse and re-cache it. */
      if (!*is_cached && rs->raw_window_cache)
        {
          SVN_ERR(svn_cache__get_partial((void **) &cached_window, is_cached,
                                         rs->raw_window_cache, &key,
                                         parse_raw_window, NULL, result_pool));
          if (*is_cached)
            SVN_ERR(svn_cache__set(rs->window_cache, &key, cached_window,
                                   scratch_pool));
        }

      /* Return cached information. */
      if (*is_cached)
        {
          /* found it. Pass it back to the caller. */
          *window_p = cached_window->window;

          /* manipulate the RS as if we just read the data */
          rs->current = cached_window->end_offset;
          rs->chunk_index = chunk_index;
        }
    }

  return SVN_NO_ERROR;
}