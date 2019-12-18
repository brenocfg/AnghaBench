#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  working_url; int /*<<< orphan*/  url; int /*<<< orphan*/ * pool; int /*<<< orphan*/  prop_changes; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  added; int /*<<< orphan*/  relpath; int /*<<< orphan*/  name; TYPE_5__* commit_ctx; TYPE_2__* parent_dir; } ;
typedef  TYPE_1__ file_context_t ;
struct TYPE_7__ {TYPE_5__* commit_ctx; } ;
typedef  TYPE_2__ dir_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/  txn_root_url; int /*<<< orphan*/  open_batons; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ USING_HTTPV2_COMMIT_SUPPORT (TYPE_5__*) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  checkout_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_file(const char *path,
          void *parent_baton,
          svn_revnum_t base_revision,
          apr_pool_t *file_pool,
          void **file_baton)
{
  dir_context_t *parent = parent_baton;
  file_context_t *new_file;

  new_file = apr_pcalloc(file_pool, sizeof(*new_file));
  new_file->pool = file_pool;

  new_file->parent_dir = parent;
  new_file->commit_ctx = parent->commit_ctx;
  new_file->relpath = apr_pstrdup(new_file->pool, path);
  new_file->name = svn_relpath_basename(new_file->relpath, NULL);
  new_file->added = FALSE;
  new_file->base_revision = base_revision;
  new_file->prop_changes = apr_hash_make(new_file->pool);

  parent->commit_ctx->open_batons++;

  if (USING_HTTPV2_COMMIT_SUPPORT(parent->commit_ctx))
    {
      new_file->url = svn_path_url_add_component2(parent->commit_ctx->txn_root_url,
                                                  path, new_file->pool);
    }
  else
    {
      /* CHECKOUT the file into our activity. */
      SVN_ERR(checkout_file(new_file, new_file->pool /* scratch_pool */));

      new_file->url = new_file->working_url;
    }

  *file_baton = new_file;

  return SVN_NO_ERROR;
}