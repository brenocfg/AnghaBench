#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wbuf_small ;
typedef  char uint8_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ptls_t ;
struct TYPE_14__ {scalar_t__ early_data_acceptance; size_t* max_early_data_size; } ;
struct TYPE_15__ {TYPE_1__ client; } ;
typedef  TYPE_2__ ptls_handshake_properties_t ;
typedef  int /*<<< orphan*/  ptls_context_t ;
struct TYPE_16__ {scalar_t__ off; char* base; } ;
typedef  TYPE_3__ ptls_buffer_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  bytebuf ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PTLS_ALERT_CLOSE_NOTIFY ; 
 int /*<<< orphan*/  PTLS_ALERT_LEVEL_WARNING ; 
 scalar_t__ PTLS_EARLY_DATA_ACCEPTANCE_UNKNOWN ; 
 scalar_t__ PTLS_EARLY_DATA_ACCEPTED ; 
 int PTLS_ERROR_IN_PROGRESS ; 
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  ptls_buffer_init (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  ptls_buffer_pushv (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  ptls_free (int /*<<< orphan*/ *) ; 
 int ptls_handshake (int /*<<< orphan*/ *,TYPE_3__*,char*,size_t*,TYPE_2__*) ; 
 scalar_t__ ptls_is_server (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ptls_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ptls_receive (int /*<<< orphan*/ *,TYPE_3__*,char*,size_t*) ; 
 int ptls_send (int /*<<< orphan*/ *,TYPE_3__*,char*,int) ; 
 int ptls_send_alert (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_set_server_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_update_key (int /*<<< orphan*/ *,int) ; 
 int read (int,char*,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  shift_buffer (TYPE_3__*,int) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int write (int,char*,scalar_t__) ; 

__attribute__((used)) static int handle_connection(int sockfd, ptls_context_t *ctx, const char *server_name, const char *input_file,
                             ptls_handshake_properties_t *hsprop, int request_key_update, int keep_sender_open)
{
    ptls_t *tls = ptls_new(ctx, server_name == NULL);
    ptls_buffer_t rbuf, encbuf, ptbuf;
    char bytebuf[16384];
    enum { IN_HANDSHAKE, IN_1RTT, IN_SHUTDOWN } state = IN_HANDSHAKE;
    int inputfd = 0, ret = 0;
    size_t early_bytes_sent = 0;
    ssize_t ioret;

    ptls_buffer_init(&rbuf, "", 0);
    ptls_buffer_init(&encbuf, "", 0);
    ptls_buffer_init(&ptbuf, "", 0);

    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    if (input_file != NULL) {
        if ((inputfd = open(input_file, O_RDONLY)) == -1) {
            fprintf(stderr, "failed to open file:%s:%s\n", input_file, strerror(errno));
            ret = 1;
            goto Exit;
        }
    }
    if (server_name != NULL) {
        ptls_set_server_name(tls, server_name, 0);
        if ((ret = ptls_handshake(tls, &encbuf, NULL, NULL, hsprop)) != PTLS_ERROR_IN_PROGRESS) {
            fprintf(stderr, "ptls_handshake:%d\n", ret);
            ret = 1;
            goto Exit;
        }
    }

    while (1) {
        /* check if data is available */
        fd_set readfds, writefds, exceptfds;
        int maxfd = 0;
        struct timeval timeout;
        do {
            FD_ZERO(&readfds);
            FD_ZERO(&writefds);
            FD_ZERO(&exceptfds);
            FD_SET(sockfd, &readfds);
            if (encbuf.off != 0)
                FD_SET(sockfd, &writefds);
            FD_SET(sockfd, &exceptfds);
            maxfd = sockfd + 1;
            if (inputfd != -1) {
                FD_SET(inputfd, &readfds);
                FD_SET(inputfd, &exceptfds);
                if (maxfd <= inputfd)
                    maxfd = inputfd + 1;
            }
            timeout.tv_sec = encbuf.off != 0 ? 0 : 3600;
            timeout.tv_usec = 0;
        } while (select(maxfd, &readfds, &writefds, &exceptfds, &timeout) == -1);

        /* consume incoming messages */
        if (FD_ISSET(sockfd, &readfds) || FD_ISSET(sockfd, &exceptfds)) {
            size_t off = 0, leftlen;
            while ((ioret = read(sockfd, bytebuf, sizeof(bytebuf))) == -1 && errno == EINTR)
                ;
            if (ioret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN)) {
                /* no data */
                ioret = 0;
            } else if (ioret <= 0) {
                goto Exit;
            }
            while ((leftlen = ioret - off) != 0) {
                if (state == IN_HANDSHAKE) {
                    if ((ret = ptls_handshake(tls, &encbuf, bytebuf + off, &leftlen, hsprop)) == 0) {
                        state = IN_1RTT;
                        assert(ptls_is_server(tls) || hsprop->client.early_data_acceptance != PTLS_EARLY_DATA_ACCEPTANCE_UNKNOWN);
                        /* release data sent as early-data, if server accepted it */
                        if (hsprop->client.early_data_acceptance == PTLS_EARLY_DATA_ACCEPTED)
                            shift_buffer(&ptbuf, early_bytes_sent);
                        if (request_key_update)
                            ptls_update_key(tls, 1);
                        if (ptbuf.off != 0) {
                            if ((ret = ptls_send(tls, &encbuf, ptbuf.base, ptbuf.off)) != 0) {
                                fprintf(stderr, "ptls_send(1rtt):%d\n", ret);
                                goto Exit;
                            }
                            ptbuf.off = 0;
                        }
                    } else if (ret == PTLS_ERROR_IN_PROGRESS) {
                        /* ok */
                    } else {
                        if (encbuf.off != 0)
                            (void)write(sockfd, encbuf.base, encbuf.off);
                        fprintf(stderr, "ptls_handshake:%d\n", ret);
                        goto Exit;
                    }
                } else {
                    if ((ret = ptls_receive(tls, &rbuf, bytebuf + off, &leftlen)) == 0) {
                        if (rbuf.off != 0) {
                            write(1, rbuf.base, rbuf.off);
                            rbuf.off = 0;
                        }
                    } else if (ret == PTLS_ERROR_IN_PROGRESS) {
                        /* ok */
                    } else {
                        fprintf(stderr, "ptls_receive:%d\n", ret);
                        goto Exit;
                    }
                }
                off += leftlen;
            }
        }

        /* read input (and send if possible) */
        if (inputfd != -1 && (FD_ISSET(inputfd, &readfds) || FD_ISSET(inputfd, &exceptfds))) {
            while ((ioret = read(inputfd, bytebuf, sizeof(bytebuf))) == -1 && errno == EINTR)
                ;
            if (ioret > 0) {
                ptls_buffer_pushv(&ptbuf, bytebuf, ioret);
                if (state == IN_HANDSHAKE) {
                    size_t send_amount = 0;
                    if (server_name != NULL && hsprop->client.max_early_data_size != NULL) {
                        size_t max_can_be_sent = *hsprop->client.max_early_data_size;
                        if (max_can_be_sent > ptbuf.off)
                            max_can_be_sent = ptbuf.off;
                        send_amount = max_can_be_sent - early_bytes_sent;
                    }
                    if (send_amount != 0) {
                        if ((ret = ptls_send(tls, &encbuf, ptbuf.base, send_amount)) != 0) {
                            fprintf(stderr, "ptls_send(early_data):%d\n", ret);
                            goto Exit;
                        }
                        early_bytes_sent += send_amount;
                    }
                } else {
                    if ((ret = ptls_send(tls, &encbuf, bytebuf, ioret)) != 0) {
                        fprintf(stderr, "ptls_send(1rtt):%d\n", ret);
                        goto Exit;
                    }
                    ptbuf.off = 0;
                }
            } else {
                /* closed */
                if (input_file != NULL)
                    close(inputfd);
                inputfd = -1;
            }
        }

        /* send any data */
        if (encbuf.off != 0) {
            while ((ioret = write(sockfd, encbuf.base, encbuf.off)) == -1 && errno == EINTR)
                ;
            if (ioret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN)) {
                /* no data */
            } else if (ioret <= 0) {
                goto Exit;
            } else {
                shift_buffer(&encbuf, ioret);
            }
        }

        /* close the sender side when necessary */
        if (state == IN_1RTT && inputfd == -1) {
            if (!keep_sender_open) {
                ptls_buffer_t wbuf;
                uint8_t wbuf_small[32];
                ptls_buffer_init(&wbuf, wbuf_small, sizeof(wbuf_small));
                if ((ret = ptls_send_alert(tls, &wbuf,
                           PTLS_ALERT_LEVEL_WARNING, PTLS_ALERT_CLOSE_NOTIFY)) != 0) {
                    fprintf(stderr, "ptls_send_alert:%d\n", ret);
                }
                if (wbuf.off != 0)
                    (void)write(sockfd, wbuf.base, wbuf.off);
                ptls_buffer_dispose(&wbuf);
                shutdown(sockfd, SHUT_WR);
            }
            state = IN_SHUTDOWN;
        }
    }

Exit:
    if (sockfd != -1)
        close(sockfd);
    if (input_file != NULL && inputfd != -1)
        close(inputfd);
    ptls_buffer_dispose(&rbuf);
    ptls_buffer_dispose(&encbuf);
    ptls_buffer_dispose(&ptbuf);
    ptls_free(tls);
    return ret != 0;
}