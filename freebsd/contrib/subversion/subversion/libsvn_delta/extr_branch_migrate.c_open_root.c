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
struct edit_baton {int dummy; } ;
struct dir_baton {struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct dir_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_error_t *
open_root(void *edit_baton,
          svn_revnum_t base_revision,
          apr_pool_t *pool,
          void **root_baton)
{
  struct edit_baton *eb = edit_baton;
  struct dir_baton *dir_baton = apr_palloc(pool, sizeof(*dir_baton));

  /*SVN_ERR(eb->wrapped_editor->open_root(eb->wrapped_edit_baton,
                                        base_revision,
                                        pool,
                                        &dir_baton->wrapped_dir_baton));*/

  dir_baton->edit_baton = eb;

  *root_baton = dir_baton;

  return SVN_NO_ERROR;
}