#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/ * (* cancel_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ svn_editor_t ;

/* Variables and functions */
 int /*<<< orphan*/  END_CALLBACK (TYPE_1__*) ; 
 int /*<<< orphan*/  START_CALLBACK (TYPE_1__*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
check_cancel(svn_editor_t *editor)
{
  svn_error_t *err = NULL;

  if (editor->cancel_func)
    {
      START_CALLBACK(editor);
      err = editor->cancel_func(editor->cancel_baton);
      END_CALLBACK(editor);
    }

  return svn_error_trace(err);
}