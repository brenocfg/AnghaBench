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
struct TYPE_4__ {int is_detached; } ;
typedef  TYPE_1__ test_streambuf_t ;
struct TYPE_5__ {TYPE_1__* data; } ;
typedef  TYPE_2__ quicly_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  on_destroy_callcnt ; 

void on_destroy(quicly_stream_t *stream, int err)
{
    test_streambuf_t *sbuf = stream->data;
    sbuf->is_detached = 1;
    ++on_destroy_callcnt;
}