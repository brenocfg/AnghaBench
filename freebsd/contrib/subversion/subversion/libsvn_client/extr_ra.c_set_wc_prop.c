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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {TYPE_1__* ctx; int /*<<< orphan*/  base_dir_abspath; } ;
typedef  TYPE_2__ callback_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  wc_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc_prop_set4 (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_wc_prop(void *baton,
            const char *path,
            const char *name,
            const svn_string_t *value,
            apr_pool_t *pool)
{
  callback_baton_t *cb = baton;
  const char *local_abspath;

  local_abspath = svn_dirent_join(cb->base_dir_abspath, path, pool);

  /* We pass 1 for the 'force' parameter here.  Since the property is
     coming from the repository, we definitely want to accept it.
     Ideally, we'd raise a conflict if, say, the received property is
     svn:eol-style yet the file has a locally added svn:mime-type
     claiming that it's binary.  Probably the repository is still
     right, but the conflict would remind the user to make sure.
     Unfortunately, we don't have a clean mechanism for doing that
     here, so we just set the property and hope for the best. */
  return svn_error_trace(svn_wc_prop_set4(cb->ctx->wc_ctx, local_abspath,
                                          name,
                                          value, svn_depth_empty,
                                          TRUE /* skip_checks */,
                                          NULL /* changelist_filter */,
                                          NULL, NULL /* cancellation */,
                                          NULL, NULL /* notification */,
                                          pool));
}