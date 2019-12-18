#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {TYPE_2__* cur_file; int /*<<< orphan*/  switched_paths; TYPE_3__* cur_dir; } ;
typedef  TYPE_1__ report_context_t ;
struct TYPE_8__ {void* copyfrom_rev; void* base_rev; void* repos_relpath; void* relpath; int /*<<< orphan*/  base_name; TYPE_3__* parent_dir; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ file_baton_t ;
struct TYPE_9__ {int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/  relpath; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ dir_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* svn_hash_gets (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_relpath_basename (void*,int /*<<< orphan*/ *) ; 
 void* svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_file_baton(file_baton_t **new_file,
                  report_context_t *ctx,
                  const char *name,
                  apr_pool_t *scratch_pool)
{
  dir_baton_t *parent = ctx->cur_dir;
  apr_pool_t *file_pool;
  file_baton_t *file;

  file_pool = svn_pool_create(parent->pool);

  file = apr_pcalloc(file_pool, sizeof(*file));
  file->pool = file_pool;

  file->parent_dir = parent;
  parent->ref_count++;

  file->relpath = svn_relpath_join(parent->relpath, name, file_pool);
  file->base_name = svn_relpath_basename(file->relpath, NULL);

  file->repos_relpath = svn_hash_gets(ctx->switched_paths, file->relpath);
  if (!file->repos_relpath)
    file->repos_relpath = svn_relpath_join(parent->repos_relpath, name,
                                           file_pool);

  /* Sane defaults */
  file->base_rev = SVN_INVALID_REVNUM;
  file->copyfrom_rev = SVN_INVALID_REVNUM;

  *new_file = file;

  ctx->cur_file = file;

  return SVN_NO_ERROR;
}