#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_3__ {struct TYPE_3__* next; struct TYPE_3__* first_substream; int /*<<< orphan*/  packed; } ;
typedef  TYPE_1__ svn_packed__byte_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_stringbuf_appendstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
append_byte_stream(svn_packed__byte_stream_t *stream,
                   svn_stringbuf_t *combined)
{
  svn_stringbuf_appendstr(combined, stream->packed);

  for (stream = stream->first_substream; stream; stream = stream->next)
    append_byte_stream(stream, combined);
}