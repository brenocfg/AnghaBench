#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  packet_buffering; } ;
struct TYPE_7__ {scalar_t__ is_buffer_indicator; } ;
typedef  TYPE_1__ PacketQueue ;
typedef  TYPE_2__ FFPlayer ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int*) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffp_toggle_buffering (TYPE_2__*,int) ; 
 int packet_queue_get (TYPE_1__*,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int packet_queue_get_or_buffering(FFPlayer *ffp, PacketQueue *q, AVPacket *pkt, int *serial, int *finished)
{
    assert(finished);
    if (!ffp->packet_buffering)
        return packet_queue_get(q, pkt, 1, serial);

    while (1) {
        int new_packet = packet_queue_get(q, pkt, 0, serial);
        if (new_packet < 0)
            return -1;
        else if (new_packet == 0) {
            if (q->is_buffer_indicator && !*finished)
                ffp_toggle_buffering(ffp, 1);
            new_packet = packet_queue_get(q, pkt, 1, serial);
            if (new_packet < 0)
                return -1;
        }

        if (*finished == *serial) {
            av_packet_unref(pkt);
            continue;
        }
        else
            break;
    }

    return 1;
}