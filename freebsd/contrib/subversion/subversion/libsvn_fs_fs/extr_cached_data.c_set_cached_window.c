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
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ window_cache_key_t ;
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
struct TYPE_9__ {int /*<<< orphan*/  end_offset; int /*<<< orphan*/ * window; } ;
typedef  TYPE_2__ svn_fs_fs__txdelta_cached_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {scalar_t__ window_cache; int /*<<< orphan*/  current; } ;
typedef  TYPE_3__ rep_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_window_key (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  svn_cache__set (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_cached_window(svn_txdelta_window_t *window,
                  rep_state_t *rs,
                  apr_pool_t *scratch_pool)
{
  if (rs->window_cache)
    {
      /* store the window and the first offset _past_ it */
      svn_fs_fs__txdelta_cached_window_t cached_window;
      window_cache_key_t key = {0};

      cached_window.window = window;
      cached_window.end_offset = rs->current;

      /* but key it with the start offset because that is the known state
       * when we will look it up */
      SVN_ERR(svn_cache__set(rs->window_cache,
                             get_window_key(&key, rs),
                             &cached_window,
                             scratch_pool));
    }

  return SVN_NO_ERROR;
}