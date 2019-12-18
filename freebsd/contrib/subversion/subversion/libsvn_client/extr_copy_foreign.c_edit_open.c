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
struct edit_baton_t {int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/  pool; } ;
struct dir_baton_t {int users; int /*<<< orphan*/  local_abspath; struct edit_baton_t* eb; int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct dir_baton_t* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_io_make_dir_recursively (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
edit_open(void *edit_baton,
          svn_revnum_t base_revision,
          apr_pool_t *result_pool,
          void **root_baton)
{
  struct edit_baton_t *eb = edit_baton;
  apr_pool_t *dir_pool = svn_pool_create(eb->pool);
  struct dir_baton_t *db = apr_pcalloc(dir_pool, sizeof(*db));

  db->pool = dir_pool;
  db->eb = eb;
  db->users = 1;
  db->local_abspath = eb->anchor_abspath;

  SVN_ERR(svn_io_make_dir_recursively(eb->anchor_abspath, dir_pool));

  *root_baton = db;

  return SVN_NO_ERROR;
}