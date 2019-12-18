#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct editor_baton {int /*<<< orphan*/  dedit_baton; TYPE_1__* deditor; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* abort_edit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * drive_changes (struct editor_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
abort_cb(void *baton,
         apr_pool_t *scratch_pool)
{
  struct editor_baton *eb = baton;
  svn_error_t *err;
  svn_error_t *err2;

  /* We still need to drive anything we collected in the editor to this
     point. */

  /* Drive the tree we've created. */
  err = drive_changes(eb, scratch_pool);

  err2 = eb->deditor->abort_edit(eb->dedit_baton, scratch_pool);

  if (err2)
    {
      if (err)
        svn_error_clear(err2);
      else
        err = err2;
    }

  return svn_error_trace(err);
}