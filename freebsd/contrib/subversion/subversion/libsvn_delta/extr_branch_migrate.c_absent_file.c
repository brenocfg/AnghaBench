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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
absent_file(const char *path,
            void *file_baton,
            apr_pool_t *pool)
{
  /*struct file_baton *fb = file_baton;
  struct edit_baton *eb = fb->edit_baton;*/

  /*SVN_ERR(eb->wrapped_editor->absent_file(path, fb->wrapped_file_baton,
                                          pool));*/

  return SVN_NO_ERROR;
}