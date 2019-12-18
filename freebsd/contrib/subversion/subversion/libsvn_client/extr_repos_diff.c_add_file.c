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
struct file_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  right_source; int /*<<< orphan*/  skip; int /*<<< orphan*/  pfb; int /*<<< orphan*/  pristine_props; } ;
struct edit_baton {TYPE_1__* processor; int /*<<< orphan*/  target_revision; int /*<<< orphan*/  empty_hash; } ;
struct dir_baton {int /*<<< orphan*/  pdb; struct edit_baton* edit_baton; scalar_t__ skip_children; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* file_opened ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 struct file_baton* make_file_baton (char const*,struct dir_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_diff__source_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
add_file(const char *path,
         void *parent_baton,
         const char *copyfrom_path,
         svn_revnum_t copyfrom_revision,
         apr_pool_t *pool,
         void **file_baton)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  struct file_baton *fb;

  /* ### TODO: support copyfrom? */

  fb = make_file_baton(path, pb, TRUE, pb->pool);
  *file_baton = fb;

  /* Process Skips. */
  if (pb->skip_children)
    {
      fb->skip = TRUE;
      return SVN_NO_ERROR;
    }

  fb->pristine_props = pb->edit_baton->empty_hash;

  fb->right_source = svn_diff__source_create(eb->target_revision, fb->pool);

  SVN_ERR(eb->processor->file_opened(&fb->pfb,
                                     &fb->skip,
                                     path,
                                     NULL,
                                     fb->right_source,
                                     NULL /* copy source */,
                                     pb->pdb,
                                     eb->processor,
                                     fb->pool, fb->pool));

  return SVN_NO_ERROR;
}