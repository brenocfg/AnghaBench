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
struct file_baton {char const* path; char const* url; int /*<<< orphan*/ * pool; int /*<<< orphan*/  repos_root_url; struct edit_baton* edit_baton; } ;
struct edit_baton {int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  root_url; int /*<<< orphan*/  root_path; } ;
struct dir_baton {struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct file_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_file(const char *path,
         void *parent_baton,
         const char *copyfrom_path,
         svn_revnum_t copyfrom_revision,
         apr_pool_t *pool,
         void **baton)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  struct file_baton *fb = apr_pcalloc(pool, sizeof(*fb));
  const char *full_path = svn_dirent_join(eb->root_path, path, pool);

  /* PATH is not canonicalized, i.e. it may still contain spaces etc.
   * but EB->root_url is. */
  const char *full_url = svn_path_url_add_component2(eb->root_url,
                                                     path,
                                                     pool);

  fb->edit_baton = eb;
  fb->path = full_path;
  fb->url = full_url;
  fb->repos_root_url = eb->repos_root_url;
  fb->pool = pool;

  *baton = fb;
  return SVN_NO_ERROR;
}