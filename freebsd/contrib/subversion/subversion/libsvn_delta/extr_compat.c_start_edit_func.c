#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  baton; int /*<<< orphan*/  base_revision; } ;
struct editor_baton {TYPE_2__ root; int /*<<< orphan*/  edit_pool; int /*<<< orphan*/  dedit_baton; TYPE_1__* deditor; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* open_root ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
start_edit_func(void *baton,
                svn_revnum_t base_revision)
{
  struct editor_baton *eb = baton;

  eb->root.base_revision = base_revision;

  /* For some Ev1 editors (such as the repos commit editor), the root must
     be open before can invoke any callbacks. The open_root() call sets up
     stuff (eg. open an FS txn) which will be needed.  */
  SVN_ERR(eb->deditor->open_root(eb->dedit_baton, eb->root.base_revision,
                                 eb->edit_pool, &eb->root.baton));

  return SVN_NO_ERROR;
}