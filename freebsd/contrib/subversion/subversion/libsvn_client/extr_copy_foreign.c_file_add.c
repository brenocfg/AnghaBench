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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct file_baton_t {int /*<<< orphan*/ * pool; int /*<<< orphan*/  local_abspath; struct dir_baton_t* pb; struct edit_baton_t* eb; } ;
struct edit_baton_t {int /*<<< orphan*/  anchor_abspath; } ;
struct dir_baton_t {int /*<<< orphan*/  users; int /*<<< orphan*/  pool; struct edit_baton_t* eb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_OBSTRUCTED_UPDATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct file_baton_t* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_dirent_is_under_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
file_add(const char *path,
         void *parent_baton,
         const char *copyfrom_path,
         svn_revnum_t copyfrom_revision,
         apr_pool_t *result_pool,
         void **file_baton)
{
  struct dir_baton_t *pb = parent_baton;
  struct edit_baton_t *eb = pb->eb;
  apr_pool_t *file_pool = svn_pool_create(pb->pool);
  struct file_baton_t *fb = apr_pcalloc(file_pool, sizeof(*fb));
  svn_boolean_t under_root;

  pb->users++;

  fb->pool = file_pool;
  fb->eb = eb;
  fb->pb = pb;

  SVN_ERR(svn_dirent_is_under_root(&under_root, &fb->local_abspath,
                                   eb->anchor_abspath, path, fb->pool));
  if (! under_root)
    {
      return svn_error_createf(
                    SVN_ERR_WC_OBSTRUCTED_UPDATE, NULL,
                    _("Path '%s' is not in the working copy"),
                    svn_dirent_local_style(path, fb->pool));
    }

  *file_baton = fb;
  return SVN_NO_ERROR;
}