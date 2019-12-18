#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  pool; TYPE_3__* commit_ctx; int /*<<< orphan*/  working_url; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  relpath; TYPE_2__* parent_dir; } ;
typedef  TYPE_1__ file_context_t ;
struct TYPE_6__ {struct TYPE_6__* parent_dir; int /*<<< orphan*/  relpath; int /*<<< orphan*/  working_url; scalar_t__ added; } ;
typedef  TYPE_2__ dir_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  session; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_version_url (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  retry_checkout_node (int /*<<< orphan*/ *,TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_relpath_skip_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
checkout_file(file_context_t *file,
              apr_pool_t *scratch_pool)
{
  dir_context_t *parent_dir = file->parent_dir;
  const char *checkout_url;

  /* Is one of our parent dirs newly added?  If so, we're already
   * implicitly checked out.
   */
  while (parent_dir)
    {
      if (parent_dir->added)
        {
          /* Implicitly checkout this file now. */
          SVN_ERR_ASSERT(parent_dir->working_url);
          file->working_url = svn_path_url_add_component2(
                                    parent_dir->working_url,
                                    svn_relpath_skip_ancestor(
                                      parent_dir->relpath, file->relpath),
                                    file->pool);
          return SVN_NO_ERROR;
        }
      parent_dir = parent_dir->parent_dir;
    }

  SVN_ERR(get_version_url(&checkout_url,
                          file->commit_ctx->session,
                          file->relpath, file->base_revision,
                          NULL, scratch_pool, scratch_pool));

  /* Checkout our file into the activity URL now. */
  return svn_error_trace(retry_checkout_node(&file->working_url,
                                             file->commit_ctx, checkout_url,
                                              file->pool, scratch_pool));
}