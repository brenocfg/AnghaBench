#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* free_packet ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ quicly_packet_allocator_t ;
typedef  int /*<<< orphan*/  quicly_datagram_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
typedef  int /*<<< orphan*/  packets ;
struct TYPE_5__ {TYPE_1__* packet_allocator; } ;

/* Variables and functions */
 int /*<<< orphan*/  perror (char*) ; 
 TYPE_3__* quicly_get_context (int /*<<< orphan*/ *) ; 
 int quicly_send (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int send_one (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_pending(int fd, quicly_conn_t *conn)
{
    quicly_datagram_t *packets[16];
    size_t num_packets, i;
    int ret;

    do {
        num_packets = sizeof(packets) / sizeof(packets[0]);
        if ((ret = quicly_send(conn, packets, &num_packets)) == 0) {
            for (i = 0; i != num_packets; ++i) {
                if ((ret = send_one(fd, packets[i])) == -1)
                    perror("sendmsg failed");
                ret = 0;
                quicly_packet_allocator_t *pa = quicly_get_context(conn)->packet_allocator;
                pa->free_packet(pa, packets[i]);
            }
        }
    } while (ret == 0 && num_packets == sizeof(packets) / sizeof(packets[0]));

    return ret;
}