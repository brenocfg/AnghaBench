#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tview_len; } ;
typedef  TYPE_1__ svn_txdelta_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_rev_baton {int /*<<< orphan*/  byte_count; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
delta_handler(svn_txdelta_window_t *window, void *baton)
{
  struct file_rev_baton *frb = baton;

  if (window != NULL)
    frb->byte_count += window->tview_len;

  return SVN_NO_ERROR;
}