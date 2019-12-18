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
struct TYPE_4__ {scalar_t__ buffer_used; TYPE_2__* private_data; } ;
typedef  TYPE_1__ svn_packed__int_stream_t ;
struct TYPE_5__ {scalar_t__ item_count; } ;
typedef  TYPE_2__ packed_int_private_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */

apr_size_t
svn_packed__int_count(svn_packed__int_stream_t *stream)
{
  packed_int_private_t *private_data = stream->private_data;
  return private_data->item_count + stream->buffer_used;
}