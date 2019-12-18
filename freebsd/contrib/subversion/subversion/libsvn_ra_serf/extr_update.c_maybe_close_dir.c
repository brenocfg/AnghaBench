#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {TYPE_1__* editor; } ;
typedef  TYPE_2__ report_context_t ;
struct TYPE_8__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  dir_baton; TYPE_2__* ctx; int /*<<< orphan*/  remove_props; scalar_t__ ref_count; struct TYPE_8__* parent_dir; } ;
typedef  TYPE_3__ dir_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* close_directory ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* change_file_prop ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ensure_dir_opened (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
maybe_close_dir(dir_baton_t *dir)
{
  apr_pool_t *scratch_pool = dir->pool;
  dir_baton_t *parent = dir->parent_dir;
  report_context_t *ctx = dir->ctx;

  if (--dir->ref_count)
    {
      return SVN_NO_ERROR;
    }

  SVN_ERR(ensure_dir_opened(dir, dir->pool));

  if (dir->remove_props)
    {
      apr_hash_index_t *hi;

      for (hi = apr_hash_first(scratch_pool, dir->remove_props);
           hi;
           hi = apr_hash_next(hi))
        {
          SVN_ERR(ctx->editor->change_file_prop(dir->dir_baton,
                                                apr_hash_this_key(hi),
                                                NULL /* value */,
                                                scratch_pool));
        }
    }

  SVN_ERR(dir->ctx->editor->close_directory(dir->dir_baton, scratch_pool));

  svn_pool_destroy(dir->pool /* scratch_pool */);

  if (parent)
    return svn_error_trace(maybe_close_dir(parent));
  else
    return SVN_NO_ERROR;
}