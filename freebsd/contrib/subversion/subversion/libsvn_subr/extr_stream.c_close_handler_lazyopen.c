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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {scalar_t__ real_stream; scalar_t__ open_on_close; } ;
typedef  TYPE_1__ lazyopen_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  lazyopen_if_unopened (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_stream_close (scalar_t__) ; 

__attribute__((used)) static svn_error_t *
close_handler_lazyopen(void *baton)
{
  lazyopen_baton_t *b = baton;

  if (b->open_on_close)
    SVN_ERR(lazyopen_if_unopened(b));
  if (b->real_stream)
    SVN_ERR(svn_stream_close(b->real_stream));

  return SVN_NO_ERROR;
}