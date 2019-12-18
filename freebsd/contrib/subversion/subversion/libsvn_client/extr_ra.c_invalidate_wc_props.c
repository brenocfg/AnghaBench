#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {TYPE_1__* ctx; int /*<<< orphan*/  base_dir_abspath; } ;
typedef  TYPE_2__ callback_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  wc_ctx; } ;

/* Variables and functions */
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__node_clear_dav_cache_recursive (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
invalidate_wc_props(void *baton,
                    const char *path,
                    const char *prop_name,
                    apr_pool_t *pool)
{
  callback_baton_t *cb = baton;
  const char *local_abspath;

  local_abspath = svn_dirent_join(cb->base_dir_abspath, path, pool);

  /* It's easier just to clear the whole dav_cache than to remove
     individual items from it recursively like this.  And since we
     know that the RA providers that ship with Subversion only
     invalidate the one property they use the most from this cache,
     and that we're intentionally trying to get away from the use of
     the cache altogether anyway, there's little to lose in wiping the
     whole cache.  Is it the most well-behaved approach to take?  Not
     so much.  We choose not to care.  */
  return svn_error_trace(svn_wc__node_clear_dav_cache_recursive(
                              cb->ctx->wc_ctx, local_abspath, pool));
}