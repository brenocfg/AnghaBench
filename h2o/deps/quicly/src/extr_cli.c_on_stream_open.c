#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct st_stream_data_t {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * callbacks; } ;
typedef  TYPE_3__ quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_stream_open_t ;
struct TYPE_10__ {TYPE_2__* tls; } ;
struct TYPE_7__ {scalar_t__ count; } ;
struct TYPE_8__ {TYPE_1__ certificates; } ;

/* Variables and functions */
 int /*<<< orphan*/  client_stream_callbacks ; 
 TYPE_6__ ctx ; 
 int quicly_streambuf_create (TYPE_3__*,int) ; 
 int /*<<< orphan*/  server_stream_callbacks ; 

__attribute__((used)) static int on_stream_open(quicly_stream_open_t *self, quicly_stream_t *stream)
{
    int ret;

    if ((ret = quicly_streambuf_create(stream, sizeof(struct st_stream_data_t))) != 0)
        return ret;
    stream->callbacks = ctx.tls->certificates.count != 0 ? &server_stream_callbacks : &client_stream_callbacks;
    return 0;
}