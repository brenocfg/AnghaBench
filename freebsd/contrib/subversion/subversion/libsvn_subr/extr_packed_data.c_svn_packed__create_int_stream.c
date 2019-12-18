#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* private_data; scalar_t__ buffer_used; } ;
typedef  TYPE_1__ svn_packed__int_stream_t ;
struct TYPE_9__ {int /*<<< orphan*/  int_stream_count; TYPE_1__* last_int_stream; TYPE_1__* first_int_stream; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ svn_packed__data_root_t ;
typedef  void* svn_boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/  is_last; TYPE_1__* next; int /*<<< orphan*/  pool; void* is_signed; void* diff; } ;
typedef  TYPE_3__ packed_int_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* apr_pcalloc (int /*<<< orphan*/ ,int) ; 

svn_packed__int_stream_t *
svn_packed__create_int_stream(svn_packed__data_root_t *root,
                              svn_boolean_t diff,
                              svn_boolean_t signed_ints)
{
  /* allocate and initialize the stream node */
  packed_int_private_t *private_data
    = apr_pcalloc(root->pool, sizeof(*private_data));
  svn_packed__int_stream_t *stream
    = apr_palloc(root->pool, sizeof(*stream));

  private_data->diff = diff;
  private_data->is_signed = signed_ints;
  private_data->is_last = TRUE;
  private_data->pool = root->pool;

  stream->buffer_used = 0;
  stream->private_data = private_data;

  /* maintain the ring list */
  if (root->last_int_stream)
    {
      packed_int_private_t *previous_private_data
        = root->last_int_stream->private_data;
      previous_private_data->next = stream;
      previous_private_data->is_last = FALSE;
    }
  else
    {
      root->first_int_stream = stream;
    }

  root->last_int_stream = stream;
  root->int_stream_count++;

  return stream;
}