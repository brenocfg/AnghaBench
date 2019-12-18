#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int current; scalar_t__ stream_start; scalar_t__ start_offset; TYPE_1__* buffer; } ;
typedef  TYPE_2__ svn_fs_fs__packed_number_stream_t ;
typedef  scalar_t__ apr_off_t ;
struct TYPE_4__ {scalar_t__ total_len; } ;

/* Variables and functions */

__attribute__((used)) static apr_off_t
packed_stream_offset(svn_fs_fs__packed_number_stream_t *stream)
{
  apr_off_t file_offset
       = stream->current == 0
       ? stream->start_offset
       : stream->buffer[stream->current-1].total_len + stream->start_offset;

  return file_offset - stream->stream_start;
}