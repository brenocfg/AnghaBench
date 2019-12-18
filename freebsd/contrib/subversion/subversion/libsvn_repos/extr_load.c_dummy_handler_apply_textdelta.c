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
typedef  int /*<<< orphan*/ * svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
dummy_handler_apply_textdelta(svn_txdelta_window_handler_t *handler,
                              void **handler_baton,
                              void *node_baton)
{
  /* Only called by parse_text_block() and that tests for NULL handlers. */
  *handler = NULL;
  *handler_baton = NULL;
  return SVN_NO_ERROR;
}