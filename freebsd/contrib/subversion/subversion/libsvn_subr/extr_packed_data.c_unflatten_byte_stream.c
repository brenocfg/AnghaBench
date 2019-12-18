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
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
struct TYPE_8__ {struct TYPE_8__* next; struct TYPE_8__* first_substream; TYPE_1__* packed; } ;
typedef  TYPE_3__ svn_packed__byte_stream_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_6__ {char* data; size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t) ; 

__attribute__((used)) static void
unflatten_byte_stream(svn_packed__byte_stream_t *stream,
                      svn_stringbuf_t *combined,
                      apr_size_t *offset)
{
  memcpy(stream->packed->data,
         combined->data + *offset,
         stream->packed->len);
  stream->packed->data[stream->packed->len] = '\0';

  *offset += stream->packed->len;
  for (stream = stream->first_substream; stream; stream = stream->next)
    unflatten_byte_stream(stream, combined, offset);
}