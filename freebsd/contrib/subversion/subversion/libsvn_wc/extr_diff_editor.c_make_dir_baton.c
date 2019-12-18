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
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct edit_baton_t {int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/ * pool; } ;
struct dir_baton_t {int users; int /*<<< orphan*/  compared; int /*<<< orphan*/  propchanges; int /*<<< orphan*/ * pool; int /*<<< orphan*/  depth; int /*<<< orphan*/  added; struct edit_baton_t* eb; int /*<<< orphan*/  relpath; int /*<<< orphan*/  name; int /*<<< orphan*/  local_abspath; struct dir_baton_t* parent_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 struct dir_baton_t* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_dirent_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dir_baton_t *
make_dir_baton(const char *path,
               struct dir_baton_t *parent_baton,
               struct edit_baton_t *eb,
               svn_boolean_t added,
               svn_depth_t depth,
               apr_pool_t *result_pool)
{
  apr_pool_t *dir_pool = svn_pool_create(parent_baton ? parent_baton->pool
                                                      : eb->pool);
  struct dir_baton_t *db = apr_pcalloc(dir_pool, sizeof(*db));

  db->parent_baton = parent_baton;

  /* Allocate 1 string for using as 3 strings */
  db->local_abspath = svn_dirent_join(eb->anchor_abspath, path, dir_pool);
  db->relpath = svn_dirent_skip_ancestor(eb->anchor_abspath, db->local_abspath);
  db->name = svn_dirent_basename(db->relpath, NULL);

  db->eb = eb;
  db->added = added;
  db->depth = depth;
  db->pool = dir_pool;
  db->propchanges = apr_array_make(dir_pool, 8, sizeof(svn_prop_t));
  db->compared = apr_hash_make(dir_pool);

  if (parent_baton != NULL)
    {
      parent_baton->users++;
    }

  db->users = 1;

  return db;
}