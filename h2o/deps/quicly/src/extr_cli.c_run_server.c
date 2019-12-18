#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_27__ ;
typedef  struct TYPE_30__   TYPE_24__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_11__ ;

/* Type definitions */
typedef  int uint8_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct msghdr {int msg_namelen; int msg_iovlen; struct iovec* msg_iov; struct sockaddr* msg_name; } ;
struct iovec {int* iov_base; int iov_len; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_38__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
struct TYPE_32__ {scalar_t__ node_id; scalar_t__ thread_id; } ;
struct TYPE_35__ {TYPE_8__ encrypted; TYPE_2__ plaintext; } ;
struct TYPE_37__ {scalar_t__ len; } ;
struct TYPE_34__ {TYPE_5__ dest; TYPE_7__ src; } ;
struct TYPE_33__ {int /*<<< orphan*/ * base; } ;
struct TYPE_29__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_36__ {scalar_t__ version; TYPE_4__ cid; TYPE_3__ octets; TYPE_1__ token; } ;
typedef  TYPE_6__ quicly_decoded_packet_t ;
typedef  int /*<<< orphan*/  quicly_datagram_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
typedef  int /*<<< orphan*/  quicly_address_token_plaintext_t ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  new_server_cid ;
typedef  int /*<<< orphan*/  mess ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_39__ {scalar_t__ (* cb ) (TYPE_9__*) ;} ;
struct TYPE_31__ {int /*<<< orphan*/  enc; int /*<<< orphan*/  dec; } ;
struct TYPE_30__ {int /*<<< orphan*/  master_id; } ;
struct TYPE_28__ {TYPE_9__* now; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 scalar_t__ QUICLY_MAX_CID_LEN_V1 ; 
 scalar_t__ QUICLY_PACKET_IS_INITIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ QUICLY_PACKET_IS_LONG_HEADER (int /*<<< orphan*/ ) ; 
 scalar_t__ QUICLY_PROTOCOL_VERSION ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 TYPE_27__ address_token_aead ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** conns ; 
 TYPE_11__ ctx ; 
 scalar_t__ enforce_retry ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  hexdump (char*,int*,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 TYPE_24__ next_cid ; 
 size_t num_conns ; 
 int /*<<< orphan*/  on_signal ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  ptls_iovec_init (int*,int) ; 
 int quicly_accept (int /*<<< orphan*/ **,TYPE_11__*,int /*<<< orphan*/ *,struct sockaddr*,TYPE_6__*,int /*<<< orphan*/ *,TYPE_24__*,int /*<<< orphan*/ *) ; 
 size_t quicly_decode_packet (TYPE_11__*,TYPE_6__*,int*,size_t) ; 
 scalar_t__ quicly_decrypt_address_token (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_free (int /*<<< orphan*/ *) ; 
 scalar_t__ quicly_get_first_timeout (int /*<<< orphan*/ *) ; 
 scalar_t__ quicly_is_destination (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr*,TYPE_6__*) ; 
 int /*<<< orphan*/  quicly_receive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr*,TYPE_6__*) ; 
 int /*<<< orphan*/ * quicly_send_retry (TYPE_11__*,int /*<<< orphan*/ ,struct sockaddr*,TYPE_7__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * quicly_send_stateless_reset (TYPE_11__*,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * quicly_send_version_negotiation (TYPE_11__*,struct sockaddr*,TYPE_7__,int /*<<< orphan*/ *,TYPE_8__) ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int) ; 
 size_t recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int send_one (int,int /*<<< orphan*/ *) ; 
 scalar_t__ send_pending (int,int /*<<< orphan*/ *) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_9__*) ; 
 scalar_t__ stub2 (TYPE_9__*) ; 
 scalar_t__ validate_token (struct sockaddr*,TYPE_7__,TYPE_8__,int /*<<< orphan*/ *) ; 
 int verbosity ; 

__attribute__((used)) static int run_server(struct sockaddr *sa, socklen_t salen)
{
    int fd;

    signal(SIGINT, on_signal);
    signal(SIGHUP, on_signal);

    if ((fd = socket(sa->sa_family, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("socket(2) failed");
        return 1;
    }
    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) != 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        return 1;
    }
    if (bind(fd, sa, salen) != 0) {
        perror("bind(2) failed");
        return 1;
    }

    while (1) {
        fd_set readfds;
        struct timeval *tv, tvbuf;
        do {
            int64_t timeout_at = INT64_MAX;
            size_t i;
            for (i = 0; i != num_conns; ++i) {
                int64_t conn_to = quicly_get_first_timeout(conns[i]);
                if (conn_to < timeout_at)
                    timeout_at = conn_to;
            }
            if (timeout_at != INT64_MAX) {
                int64_t delta = timeout_at - ctx.now->cb(ctx.now);
                if (delta > 0) {
                    tvbuf.tv_sec = delta / 1000;
                    tvbuf.tv_usec = (delta % 1000) * 1000;
                } else {
                    tvbuf.tv_sec = 0;
                    tvbuf.tv_usec = 0;
                }
                tv = &tvbuf;
            } else {
                tv = NULL;
            }
            FD_ZERO(&readfds);
            FD_SET(fd, &readfds);
        } while (select(fd + 1, &readfds, NULL, NULL, tv) == -1 && errno == EINTR);
        if (FD_ISSET(fd, &readfds)) {
            uint8_t buf[4096];
            struct msghdr mess;
            struct sockaddr sa;
            struct iovec vec;
            memset(&mess, 0, sizeof(mess));
            mess.msg_name = &sa;
            mess.msg_namelen = sizeof(sa);
            vec.iov_base = buf;
            vec.iov_len = sizeof(buf);
            mess.msg_iov = &vec;
            mess.msg_iovlen = 1;
            ssize_t rret;
            while ((rret = recvmsg(fd, &mess, 0)) <= 0)
                ;
            if (verbosity >= 2)
                hexdump("recvmsg", buf, rret);
            size_t off = 0;
            while (off != rret) {
                quicly_decoded_packet_t packet;
                size_t plen = quicly_decode_packet(&ctx, &packet, buf + off, rret - off);
                if (plen == SIZE_MAX)
                    break;
                if (QUICLY_PACKET_IS_LONG_HEADER(packet.octets.base[0])) {
                    if (packet.version != QUICLY_PROTOCOL_VERSION) {
                        quicly_datagram_t *rp =
                            quicly_send_version_negotiation(&ctx, &sa, packet.cid.src, NULL, packet.cid.dest.encrypted);
                        assert(rp != NULL);
                        if (send_one(fd, rp) == -1)
                            perror("sendmsg failed");
                        break;
                    }
                    /* there is no way to send response to these v1 packets */
                    if (packet.cid.dest.encrypted.len > QUICLY_MAX_CID_LEN_V1 || packet.cid.src.len > QUICLY_MAX_CID_LEN_V1)
                        break;
                }

                quicly_conn_t *conn = NULL;
                size_t i;
                for (i = 0; i != num_conns; ++i) {
                    if (quicly_is_destination(conns[i], NULL, &sa, &packet)) {
                        conn = conns[i];
                        break;
                    }
                }
                if (conn != NULL) {
                    /* existing connection */
                    quicly_receive(conn, NULL, &sa, &packet);
                } else if (QUICLY_PACKET_IS_INITIAL(packet.octets.base[0])) {
                    /* long header packet; potentially a new connection */
                    quicly_address_token_plaintext_t *token = NULL, token_buf;
                    if (packet.token.len != 0 &&
                        quicly_decrypt_address_token(address_token_aead.dec, &token_buf, packet.token.base, packet.token.len, 0) ==
                            0 &&
                        validate_token(&sa, packet.cid.src, packet.cid.dest.encrypted, &token_buf))
                        token = &token_buf;
                    if (enforce_retry && token == NULL && packet.cid.dest.encrypted.len >= 8) {
                        /* unbound connection; send a retry token unless the client has supplied the correct one, but not too many
                         */
                        uint8_t new_server_cid[8];
                        memcpy(new_server_cid, packet.cid.dest.encrypted.base, sizeof(new_server_cid));
                        new_server_cid[0] ^= 0xff;
                        quicly_datagram_t *rp = quicly_send_retry(&ctx, address_token_aead.enc, &sa, packet.cid.src, NULL,
                                                                  ptls_iovec_init(new_server_cid, sizeof(new_server_cid)),
                                                                  packet.cid.dest.encrypted, ptls_iovec_init(NULL, 0),
                                                                  ptls_iovec_init(NULL, 0));
                        assert(rp != NULL);
                        if (send_one(fd, rp) == -1)
                            perror("sendmsg failed");
                        break;
                    } else {
                        /* new connection */
                        int ret = quicly_accept(&conn, &ctx, NULL, &sa, &packet, token, &next_cid, NULL);
                        if (ret == 0) {
                            assert(conn != NULL);
                            ++next_cid.master_id;
                            conns = realloc(conns, sizeof(*conns) * (num_conns + 1));
                            assert(conns != NULL);
                            conns[num_conns++] = conn;
                        } else {
                            assert(conn == NULL);
                        }
                    }
                } else if (!QUICLY_PACKET_IS_LONG_HEADER(packet.octets.base[0])) {
                    /* short header packet; potentially a dead connection. No need to check the length of the incoming packet,
                     * because loop is prevented by authenticating the CID (by checking node_id and thread_id). If the peer is also
                     * sending a reset, then the next CID is highly likely to contain a non-authenticating CID, ... */
                    if (packet.cid.dest.plaintext.node_id == 0 && packet.cid.dest.plaintext.thread_id == 0) {
                        quicly_datagram_t *dgram = quicly_send_stateless_reset(&ctx, &sa, NULL, packet.cid.dest.encrypted.base);
                        if (send_one(fd, dgram) == -1)
                            perror("sendmsg failed");
                    }
                }
                off += plen;
            }
        }
        {
            size_t i;
            for (i = 0; i != num_conns; ++i) {
                if (quicly_get_first_timeout(conns[i]) <= ctx.now->cb(ctx.now)) {
                    if (send_pending(fd, conns[i]) != 0) {
                        quicly_free(conns[i]);
                        memmove(conns + i, conns + i + 1, (num_conns - i - 1) * sizeof(*conns));
                        --i;
                        --num_conns;
                    }
                }
            }
        }
    }
}