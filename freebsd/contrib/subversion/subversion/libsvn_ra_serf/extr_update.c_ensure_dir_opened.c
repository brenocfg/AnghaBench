#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {TYPE_3__* editor; int /*<<< orphan*/  editor_baton; int /*<<< orphan*/  update_target; TYPE_2__* sess; scalar_t__ destination; } ;
typedef  TYPE_4__ report_context_t ;
struct TYPE_11__ {char* base_name; scalar_t__ dir_opened; int /*<<< orphan*/  dir_baton; int /*<<< orphan*/  pool; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_path; struct TYPE_11__* parent_dir; int /*<<< orphan*/  relpath; int /*<<< orphan*/  base_rev; TYPE_4__* ctx; } ;
typedef  TYPE_5__ dir_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/ * (* add_directory ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* open_directory ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* open_root ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  wc_callback_baton; TYPE_1__* wc_callbacks; } ;
struct TYPE_7__ {int /*<<< orphan*/ * (* invalidate_wc_props ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SERF__WC_CHECKED_IN_URL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t*
ensure_dir_opened(dir_baton_t *dir,
                  apr_pool_t *scratch_pool)
{
  report_context_t *ctx = dir->ctx;

  if (dir->dir_opened)
    return SVN_NO_ERROR;

  if (dir->base_name[0] == '\0')
    {
      if (ctx->destination
          && ctx->sess->wc_callbacks->invalidate_wc_props)
        {
          SVN_ERR(ctx->sess->wc_callbacks->invalidate_wc_props(
                      ctx->sess->wc_callback_baton,
                      ctx->update_target,
                      SVN_RA_SERF__WC_CHECKED_IN_URL, scratch_pool));
        }

      SVN_ERR(ctx->editor->open_root(ctx->editor_baton, dir->base_rev,
                                     dir->pool,
                                     &dir->dir_baton));
    }
  else
    {
      SVN_ERR(ensure_dir_opened(dir->parent_dir, scratch_pool));

      if (SVN_IS_VALID_REVNUM(dir->base_rev))
        {
          SVN_ERR(ctx->editor->open_directory(dir->relpath,
                                              dir->parent_dir->dir_baton,
                                              dir->base_rev,
                                              dir->pool,
                                              &dir->dir_baton));
        }
      else
        {
          SVN_ERR(ctx->editor->add_directory(dir->relpath,
                                             dir->parent_dir->dir_baton,
                                             dir->copyfrom_path,
                                             dir->copyfrom_rev,
                                             dir->pool,
                                             &dir->dir_baton));
        }
    }

  dir->dir_opened = TRUE;

  return SVN_NO_ERROR;
}