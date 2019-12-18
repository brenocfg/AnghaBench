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
struct TYPE_3__ {int /*<<< orphan*/  real_stream; } ;
typedef  TYPE_1__ lazyopen_baton_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  lazyopen_if_unopened (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_full_handler_lazyopen(void *baton,
                      char *buffer,
                      apr_size_t *len)
{
  lazyopen_baton_t *b = baton;

  SVN_ERR(lazyopen_if_unopened(b));
  SVN_ERR(svn_stream_read_full(b->real_stream, buffer, len));

  return SVN_NO_ERROR;
}