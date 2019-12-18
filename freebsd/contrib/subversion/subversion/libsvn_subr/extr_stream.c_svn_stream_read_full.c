#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  baton; int /*<<< orphan*/  (* read_full_fn ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  full_read_fallback (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_stream_read_full(svn_stream_t *stream, char *buffer, apr_size_t *len)
{
  if (stream->read_full_fn == NULL)
    return svn_error_trace(full_read_fallback(stream, buffer, len));

  return svn_error_trace(stream->read_full_fn(stream->baton, buffer, len));
}