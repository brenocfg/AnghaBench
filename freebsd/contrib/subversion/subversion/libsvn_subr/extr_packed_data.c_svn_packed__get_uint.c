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
struct TYPE_4__ {scalar_t__ buffer_used; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ svn_packed__int_stream_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_packed__data_fill_buffer (TYPE_1__*) ; 

apr_uint64_t
svn_packed__get_uint(svn_packed__int_stream_t *stream)
{
  if (stream->buffer_used == 0)
    svn_packed__data_fill_buffer(stream);

  return stream->buffer_used ? stream->buffer[--stream->buffer_used] : 0;
}