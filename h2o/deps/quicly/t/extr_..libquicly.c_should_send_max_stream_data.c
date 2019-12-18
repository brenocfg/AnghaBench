#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  window; } ;
struct TYPE_7__ {scalar_t__ eos; int /*<<< orphan*/  data_off; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_stream_data_sender; } ;
struct TYPE_9__ {TYPE_3__ _recv_aux; TYPE_2__ recvstate; TYPE_1__ _send_aux; } ;
typedef  TYPE_4__ quicly_stream_t ;

/* Variables and functions */
 scalar_t__ UINT64_MAX ; 
 int quicly_maxsender_should_send_max (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int should_send_max_stream_data(quicly_stream_t *stream)
{
    if (stream->recvstate.eos != UINT64_MAX)
        return 0;
    return quicly_maxsender_should_send_max(&stream->_send_aux.max_stream_data_sender, stream->recvstate.data_off,
                                            stream->_recv_aux.window, 512);
}