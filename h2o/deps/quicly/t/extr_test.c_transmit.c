#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_decoded_packet_t ;
typedef  int /*<<< orphan*/  quicly_datagram_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
typedef  int /*<<< orphan*/  datagrams ;
struct TYPE_2__ {int /*<<< orphan*/  sa; } ;

/* Variables and functions */
 int QUICLY_ERROR_PACKET_IGNORED ; 
 size_t decode_packets (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t) ; 
 TYPE_1__ fake_address ; 
 int /*<<< orphan*/  free_packets (int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  ok (int) ; 
 int quicly_receive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int quicly_send (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 

size_t transmit(quicly_conn_t *src, quicly_conn_t *dst)
{
    quicly_datagram_t *datagrams[32];
    size_t num_datagrams, i;
    quicly_decoded_packet_t decoded[32];
    int ret;

    num_datagrams = sizeof(datagrams) / sizeof(datagrams[0]);
    ret = quicly_send(src, datagrams, &num_datagrams);
    ok(ret == 0);

    if (num_datagrams != 0) {
        size_t num_packets = decode_packets(decoded, datagrams, num_datagrams);
        for (i = 0; i != num_packets; ++i) {
            ret = quicly_receive(dst, NULL, &fake_address.sa, decoded + i);
            ok(ret == 0 || ret == QUICLY_ERROR_PACKET_IGNORED);
        }
        free_packets(datagrams, num_datagrams);
    }

    return num_datagrams;
}