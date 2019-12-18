#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {char* working_url; char* url; int /*<<< orphan*/  pool; TYPE_2__* commit_ctx; struct TYPE_4__* parent_dir; int /*<<< orphan*/  relpath; scalar_t__ added; } ;
typedef  TYPE_1__ dir_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {char* baseline_url; char* vcc_url; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (char*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  retry_checkout_node (char const**,TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 char* svn_path_url_add_component2 (char*,char const*,int /*<<< orphan*/ ) ; 
 char* svn_relpath_skip_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
checkout_dir(dir_context_t *dir,
             apr_pool_t *scratch_pool)
{
  dir_context_t *c_dir = dir;
  const char *checkout_url;
  const char **working;

  if (dir->working_url)
    {
      return SVN_NO_ERROR;
    }

  /* Is this directory or one of our parent dirs newly added?
   * If so, we're already implicitly checked out. */
  while (c_dir)
    {
      if (c_dir->added)
        {
          /* Calculate the working_url by skipping the shared ancestor between
           * the c_dir_parent->relpath and dir->relpath. This is safe since an
           * add is guaranteed to have a parent that is checked out. */
          dir_context_t *c_dir_parent = c_dir->parent_dir;
          const char *relpath = svn_relpath_skip_ancestor(c_dir_parent->relpath,
                                                          dir->relpath);

          /* Implicitly checkout this dir now. */
          SVN_ERR_ASSERT(c_dir_parent->working_url);
          dir->working_url = svn_path_url_add_component2(
                                   c_dir_parent->working_url,
                                   relpath, dir->pool);
          return SVN_NO_ERROR;
        }
      c_dir = c_dir->parent_dir;
    }

  /* We could be called twice for the root: once to checkout the baseline;
   * once to checkout the directory itself if we need to do so.
   * Note: CHECKOUT_URL should live longer than HANDLER.
   */
  if (!dir->parent_dir && !dir->commit_ctx->baseline_url)
    {
      checkout_url = dir->commit_ctx->vcc_url;
      working = &dir->commit_ctx->baseline_url;
    }
  else
    {
      checkout_url = dir->url;
      working = &dir->working_url;
    }

  /* Checkout our directory into the activity URL now. */
  return svn_error_trace(retry_checkout_node(working, dir->commit_ctx,
                                             checkout_url,
                                             dir->pool, scratch_pool));
}