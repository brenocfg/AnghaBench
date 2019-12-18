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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct file_baton_t {int /*<<< orphan*/  propchanges; int /*<<< orphan*/ * pool; int /*<<< orphan*/  added; int /*<<< orphan*/  relpath; int /*<<< orphan*/  name; int /*<<< orphan*/  local_abspath; struct dir_baton_t* parent_baton; struct edit_baton_t* eb; } ;
struct edit_baton_t {int /*<<< orphan*/  anchor_abspath; } ;
struct dir_baton_t {int /*<<< orphan*/  users; struct edit_baton_t* eb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 struct file_baton_t* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_dirent_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct file_baton_t *
make_file_baton(const char *path,
                svn_boolean_t added,
                struct dir_baton_t *parent_baton,
                apr_pool_t *result_pool)
{
  apr_pool_t *file_pool = svn_pool_create(result_pool);
  struct file_baton_t *fb = apr_pcalloc(file_pool, sizeof(*fb));
  struct edit_baton_t *eb = parent_baton->eb;

  fb->eb = eb;
  fb->parent_baton = parent_baton;
  fb->parent_baton->users++;

  /* Allocate 1 string for using as 3 strings */
  fb->local_abspath = svn_dirent_join(eb->anchor_abspath, path, file_pool);
  fb->relpath = svn_dirent_skip_ancestor(eb->anchor_abspath, fb->local_abspath);
  fb->name = svn_dirent_basename(fb->relpath, NULL);

  fb->added = added;
  fb->pool = file_pool;
  fb->propchanges  = apr_array_make(file_pool, 8, sizeof(svn_prop_t));

  return fb;
}