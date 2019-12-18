#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_7__ {TYPE_3__* private_data; } ;
typedef  TYPE_2__ svn_packed__int_stream_t ;
struct TYPE_8__ {int substream_count; int item_count; TYPE_2__* next; scalar_t__ is_last; TYPE_2__* first_substream; TYPE_1__* packed; scalar_t__ is_signed; scalar_t__ diff; } ;
typedef  TYPE_3__ packed_int_private_t ;
struct TYPE_6__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  data_flush_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  write_packed_uint (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
write_int_stream_structure(svn_stringbuf_t* tree_struct,
                           svn_packed__int_stream_t* stream)
{
  while (stream)
    {
      /* store config parameters and number of sub-streams in 1 number */
      packed_int_private_t *private_data = stream->private_data;
      write_packed_uint(tree_struct, (private_data->substream_count << 2)
                                   + (private_data->diff ? 1 : 0)
                                   + (private_data->is_signed ? 2 : 0));

      /* store item count and length their of packed representation */
      data_flush_buffer(stream);

      write_packed_uint(tree_struct, private_data->item_count);
      write_packed_uint(tree_struct, private_data->packed
                                   ? private_data->packed->len
                                   : 0);

      /* append all sub-stream structures */
      write_int_stream_structure(tree_struct, private_data->first_substream);

      /* continue with next sibling */
      stream = private_data->is_last ? NULL : private_data->next;
    }
}