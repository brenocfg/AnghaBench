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
struct TYPE_4__ {size_t buffer_used; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ svn_packed__int_stream_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;

/* Variables and functions */
 scalar_t__ SVN__PACKED_DATA_BUFFER_SIZE ; 
 int /*<<< orphan*/  data_flush_buffer (TYPE_1__*) ; 

void
svn_packed__add_uint(svn_packed__int_stream_t *stream,
                     apr_uint64_t value)
{
  stream->buffer[stream->buffer_used] = value;
  if (++stream->buffer_used == SVN__PACKED_DATA_BUFFER_SIZE)
    data_flush_buffer(stream);
}