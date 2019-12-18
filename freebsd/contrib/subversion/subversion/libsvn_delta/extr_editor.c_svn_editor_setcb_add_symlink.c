#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  cb_add_symlink; } ;
struct TYPE_5__ {TYPE_1__ funcs; } ;
typedef  TYPE_2__ svn_editor_t ;
typedef  int /*<<< orphan*/  svn_editor_cb_add_symlink_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

svn_error_t *
svn_editor_setcb_add_symlink(svn_editor_t *editor,
                             svn_editor_cb_add_symlink_t callback,
                             apr_pool_t *scratch_pool)
{
  editor->funcs.cb_add_symlink = callback;
  return SVN_NO_ERROR;
}