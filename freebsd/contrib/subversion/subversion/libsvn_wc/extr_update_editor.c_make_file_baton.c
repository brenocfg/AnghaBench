#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_prop_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct file_baton {int shadowed; void* changed_rev; struct dir_baton* dir_baton; int /*<<< orphan*/  skip_this; void* add_existed; void* obstruction_found; int /*<<< orphan*/  adding_file; int /*<<< orphan*/  bump_info; int /*<<< orphan*/  propchanges; int /*<<< orphan*/  edit_baton; int /*<<< orphan*/ * pool; int /*<<< orphan*/  name; int /*<<< orphan*/  local_abspath; void* old_revision; } ;
struct dir_baton {int /*<<< orphan*/  ref_count; scalar_t__ edit_obstructed; scalar_t__ shadowed; int /*<<< orphan*/  skip_this; int /*<<< orphan*/  bump_info; int /*<<< orphan*/  edit_baton; int /*<<< orphan*/  local_abspath; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (char const*) ; 
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 struct file_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  path_join_under_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
make_file_baton(struct file_baton **f_p,
                struct dir_baton *pb,
                const char *path,
                svn_boolean_t adding,
                apr_pool_t *scratch_pool)
{
  apr_pool_t *file_pool = svn_pool_create(pb->pool);
  struct file_baton *f = apr_pcalloc(file_pool, sizeof(*f));

  SVN_ERR_ASSERT(path);

  /* Make the file's on-disk name. */
  f->name = svn_dirent_basename(path, file_pool);
  f->old_revision = SVN_INVALID_REVNUM;
  SVN_ERR(path_join_under_root(&f->local_abspath,
                               pb->local_abspath, f->name, file_pool));

  f->pool              = file_pool;
  f->edit_baton        = pb->edit_baton;
  f->propchanges       = apr_array_make(file_pool, 1, sizeof(svn_prop_t));
  f->bump_info         = pb->bump_info;
  f->adding_file       = adding;
  f->obstruction_found = FALSE;
  f->add_existed       = FALSE;
  f->skip_this         = pb->skip_this;
  f->shadowed          = pb->shadowed || pb->edit_obstructed;
  f->dir_baton         = pb;
  f->changed_rev       = SVN_INVALID_REVNUM;

  /* the directory has one more referer now */
  pb->ref_count++;

  *f_p = f;
  return SVN_NO_ERROR;
}