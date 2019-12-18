#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
typedef  scalar_t__ svn_boolean_t ;
struct file_baton {int /*<<< orphan*/  pfb; int /*<<< orphan*/  pristine_props; int /*<<< orphan*/  path_start_revision; int /*<<< orphan*/  path; } ;
struct edit_baton {TYPE_1__* processor; int /*<<< orphan*/  text_deltas; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  (* cancel_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  revision; } ;
struct dir_baton {int /*<<< orphan*/  pdb; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* file_deleted ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* file_opened ) (int /*<<< orphan*/ *,scalar_t__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_file_from_ra (struct file_baton*,int,int /*<<< orphan*/ *) ; 
 struct file_baton* make_file_baton (char const*,struct dir_baton*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,scalar_t__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_diff__source_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
diff_deleted_file(const char *path,
                  struct dir_baton *db,
                  apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = db->edit_baton;
  struct file_baton *fb = make_file_baton(path, db, FALSE, scratch_pool);
  svn_boolean_t skip = FALSE;
  svn_diff_source_t *left_source = svn_diff__source_create(eb->revision,
                                                           scratch_pool);

  if (eb->cancel_func)
    SVN_ERR(eb->cancel_func(eb->cancel_baton));

  SVN_ERR(eb->processor->file_opened(&fb->pfb, &skip, path,
                                     left_source,
                                     NULL /* right_source */,
                                     NULL /* copyfrom_source */,
                                     db->pdb,
                                     eb->processor,
                                     scratch_pool, scratch_pool));

  if (eb->cancel_func)
    SVN_ERR(eb->cancel_func(eb->cancel_baton));

  if (skip)
    return SVN_NO_ERROR;

  SVN_ERR(get_file_from_ra(fb, ! eb->text_deltas, scratch_pool));

  SVN_ERR(eb->processor->file_deleted(fb->path,
                                      left_source,
                                      fb->path_start_revision,
                                      fb->pristine_props,
                                      fb->pfb,
                                      eb->processor,
                                      scratch_pool));

  return SVN_NO_ERROR;
}