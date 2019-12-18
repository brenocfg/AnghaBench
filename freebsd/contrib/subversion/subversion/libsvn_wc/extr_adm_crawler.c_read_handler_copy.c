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
struct copying_stream_baton {int /*<<< orphan*/  target; int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_handler_copy(void *baton, char *buffer, apr_size_t *len)
{
  struct copying_stream_baton *btn = baton;

  SVN_ERR(svn_stream_read_full(btn->source, buffer, len));

  return svn_stream_write(btn->target, buffer, len);
}