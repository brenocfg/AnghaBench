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
struct copying_stream_baton {int /*<<< orphan*/  source; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
close_handler_copy(void *baton)
{
  struct copying_stream_baton *btn = baton;

  SVN_ERR(svn_stream_close(btn->target));
  return svn_stream_close(btn->source);
}