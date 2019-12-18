#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svn_wc__db_info_t {scalar_t__ kind; scalar_t__ status; } ;
struct file_baton_t {int /*<<< orphan*/  pool; void* right_src; void* left_src; int /*<<< orphan*/  relpath; void* skip; int /*<<< orphan*/  pfb; int /*<<< orphan*/  name; void* ignoring_ancestry; void* repos_only; } ;
struct edit_baton_t {TYPE_1__* processor; int /*<<< orphan*/  revnum; int /*<<< orphan*/  ignore_ancestry; } ;
struct dir_baton_t {int /*<<< orphan*/  pdb; int /*<<< orphan*/  pool; int /*<<< orphan*/  compared; int /*<<< orphan*/  local_info; scalar_t__ repos_only; scalar_t__ skip_children; struct edit_baton_t* eb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* file_opened ) (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ NOT_PRESENT (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_local_info (struct dir_baton_t*,int /*<<< orphan*/ *) ; 
 struct file_baton_t* make_file_baton (char const*,void*,struct dir_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* svn_diff__source_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct svn_wc__db_info_t* svn_hash_gets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_wc__db_status_added ; 

__attribute__((used)) static svn_error_t *
add_file(const char *path,
         void *parent_baton,
         const char *copyfrom_path,
         svn_revnum_t copyfrom_revision,
         apr_pool_t *file_pool,
         void **file_baton)
{
  struct dir_baton_t *pb = parent_baton;
  struct edit_baton_t *eb = pb->eb;
  struct file_baton_t *fb;

  fb = make_file_baton(path, TRUE, pb, file_pool);
  *file_baton = fb;

  if (pb->skip_children)
    {
      fb->skip = TRUE;
      return SVN_NO_ERROR;
    }
  else if (pb->repos_only || !eb->ignore_ancestry)
    fb->repos_only = TRUE;
  else
    {
      struct svn_wc__db_info_t *info;
      SVN_ERR(ensure_local_info(pb, file_pool));

      info = svn_hash_gets(pb->local_info, fb->name);

      if (!info || info->kind != svn_node_file || NOT_PRESENT(info->status))
        fb->repos_only = TRUE;

      if (!fb->repos_only && info->status != svn_wc__db_status_added)
        fb->repos_only = TRUE;

      if (!fb->repos_only)
        {
          /* Add this path to the parent directory's list of elements that
             have been compared. */
          fb->right_src = svn_diff__source_create(SVN_INVALID_REVNUM, fb->pool);
          fb->ignoring_ancestry = TRUE;

          svn_hash_sets(pb->compared, apr_pstrdup(pb->pool, fb->name), "");
        }
    }

  fb->left_src = svn_diff__source_create(eb->revnum, fb->pool);

  SVN_ERR(eb->processor->file_opened(&fb->pfb, &fb->skip,
                                     fb->relpath,
                                     fb->left_src,
                                     fb->right_src,
                                     NULL /* copyfrom src */,
                                     pb->pdb,
                                     eb->processor,
                                     fb->pool, fb->pool));

  return SVN_NO_ERROR;
}