#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_storage {int dummy; } ;
struct msghdr {int msg_namelen; int msg_iovlen; struct iovec* msg_iov; struct sockaddr_storage* msg_name; } ;
struct iovec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  quicly_datagram_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  dgrams ;
typedef  int /*<<< orphan*/  conns ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {TYPE_1__* packet_allocator; TYPE_2__* now; } ;
struct TYPE_5__ {scalar_t__ (* cb ) (TYPE_2__*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* free_packet ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ INT64_MAX ; 
#define  QUICLY_ERROR_FREE_CONNECTION 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__ ctx ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  forward_stdin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  is_server () ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ **,struct msghdr*,int) ; 
 int /*<<< orphan*/  quicly_free (int /*<<< orphan*/ *) ; 
 scalar_t__ quicly_get_first_timeout (int /*<<< orphan*/ *) ; 
 int quicly_send (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  send_one (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_loop(int fd, quicly_conn_t *client)
{
    quicly_conn_t *conns[256] = {client}; /* a null-terminated list of connections; proper app should use a hashmap or something */
    size_t i;
    int read_stdin = client != NULL;

    while (1) {

        /* wait for sockets to become readable, or some event in the QUIC stack to fire */
        fd_set readfds;
        struct timeval tv;
        do {
            int64_t first_timeout = INT64_MAX, now = ctx.now->cb(ctx.now);
            for (i = 0; conns[i] != NULL; ++i) {
                int64_t conn_timeout = quicly_get_first_timeout(conns[i]);
                if (conn_timeout < first_timeout)
                    first_timeout = conn_timeout;
            }
            if (now < first_timeout) {
                int64_t delta = first_timeout - now;
                if (delta > 1000 * 1000)
                    delta = 1000 * 1000;
                tv.tv_sec = delta / 1000;
                tv.tv_usec = (delta % 1000) * 1000;
            } else {
                tv.tv_sec = 1000;
                tv.tv_usec = 0;
            }
            FD_ZERO(&readfds);
            FD_SET(fd, &readfds);
            /* we want to read input from stdin */
            if (read_stdin)
                FD_SET(0, &readfds);
        } while (select(fd + 1, &readfds, NULL, NULL, &tv) == -1 && errno == EINTR);

        /* read the QUIC fd */
        if (FD_ISSET(fd, &readfds)) {
            uint8_t buf[4096];
            struct sockaddr_storage sa;
            struct iovec vec = {.iov_base = buf, .iov_len = sizeof(buf)};
            struct msghdr msg = {.msg_name = &sa, .msg_namelen = sizeof(sa), .msg_iov = &vec, .msg_iovlen = 1};
            ssize_t rret;
            while ((rret = recvmsg(fd, &msg, 0)) == -1 && errno == EINTR)
                ;
            if (rret > 0)
                process_msg(client != NULL, conns, &msg, rret);
        }

        /* read stdin, send the input to the active stram */
        if (FD_ISSET(0, &readfds)) {
            assert(client != NULL);
            if (!forward_stdin(client))
                read_stdin = 0;
        }

        /* send QUIC packets, if any */
        for (i = 0; conns[i] != NULL; ++i) {
            quicly_datagram_t *dgrams[16];
            size_t num_dgrams = sizeof(dgrams) / sizeof(dgrams[0]);
            int ret = quicly_send(conns[i], dgrams, &num_dgrams);
            switch (ret) {
            case 0: {
                size_t j;
                for (j = 0; j != num_dgrams; ++j) {
                    send_one(fd, dgrams[j]);
                    ctx.packet_allocator->free_packet(ctx.packet_allocator, dgrams[j]);
                }
            } break;
            case QUICLY_ERROR_FREE_CONNECTION:
                /* connection has been closed, free, and exit when running as a client */
                quicly_free(conns[i]);
                memmove(conns + i, conns + i + 1, sizeof(conns) - sizeof(conns[0]) * (i + 1));
                --i;
                if (!is_server())
                    return 0;
                break;
            default:
                fprintf(stderr, "quicly_send returned %d\n", ret);
                return 1;
            }
        }
    }

    return 0;
}