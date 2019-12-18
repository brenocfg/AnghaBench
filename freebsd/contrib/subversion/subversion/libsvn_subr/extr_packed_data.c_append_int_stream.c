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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_4__ {TYPE_2__* private_data; } ;
typedef  TYPE_1__ svn_packed__int_stream_t ;
struct TYPE_5__ {TYPE_1__* next; scalar_t__ is_last; TYPE_1__* first_substream; scalar_t__ packed; } ;
typedef  TYPE_2__ packed_int_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_stringbuf_appendstr (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
append_int_stream(svn_packed__int_stream_t *stream,
                  svn_stringbuf_t *combined)
{
  packed_int_private_t *private_data = stream->private_data;
  if (private_data->packed)
    svn_stringbuf_appendstr(combined, private_data->packed);

  stream = private_data->first_substream;
  while (stream)
    {
      private_data = stream->private_data;
      append_int_stream(stream, combined);
      stream = private_data->is_last ? NULL : private_data->next;
    }
}