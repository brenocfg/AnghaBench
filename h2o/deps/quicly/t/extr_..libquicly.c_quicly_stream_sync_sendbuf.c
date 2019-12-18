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
struct TYPE_4__ {int /*<<< orphan*/  sendstate; } ;
typedef  TYPE_1__ quicly_stream_t ;

/* Variables and functions */
 int quicly_sendstate_activate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resched_stream_data (TYPE_1__*) ; 

int quicly_stream_sync_sendbuf(quicly_stream_t *stream, int activate)
{
    int ret;

    if (activate) {
        if ((ret = quicly_sendstate_activate(&stream->sendstate)) != 0)
            return ret;
    }

    resched_stream_data(stream);
    return 0;
}