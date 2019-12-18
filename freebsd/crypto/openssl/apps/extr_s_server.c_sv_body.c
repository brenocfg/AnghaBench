#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_4__ {int /*<<< orphan*/  info; } ;
struct TYPE_3__ {TYPE_2__* user; int /*<<< orphan*/  login; int /*<<< orphan*/  vb; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CTRL_DGRAM_MTU_DISCOVER ; 
 int /*<<< orphan*/  BIO_CTRL_DGRAM_SET_RECV_TIMEOUT ; 
 int /*<<< orphan*/  BIO_CTRL_DGRAM_SET_SEND_TIMEOUT ; 
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_closesocket (int) ; 
 int /*<<< orphan*/  BIO_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  BIO_f_nbio_test () ; 
 int /*<<< orphan*/  BIO_flush (scalar_t__) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_dgram (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_dgram_sctp (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_socket (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_callback_arg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_socket_nbio (int,int) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ DGRAM_RCV_TIMEOUT ; 
 scalar_t__ DGRAM_SND_TIMEOUT ; 
 scalar_t__ DTLS1_VERSION ; 
 scalar_t__ DTLS_get_link_min_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DTLS_set_link_mtu (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ DTLSv1_get_timeout (int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ DTLSv1_handle_timeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_print_errors (scalar_t__) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int IPPROTO_SCTP ; 
 int /*<<< orphan*/  OPENSSL_clear_free (char*,int) ; 
 int SOCK_DGRAM ; 
 void* SRP_VBASE_get1_by_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRP_user_pwd_free (TYPE_2__*) ; 
 scalar_t__ SSL_EARLY_DATA_NOT_SENT ; 
#define  SSL_ERROR_NONE 136 
#define  SSL_ERROR_SSL 135 
#define  SSL_ERROR_SYSCALL 134 
#define  SSL_ERROR_WANT_ASYNC 133 
#define  SSL_ERROR_WANT_ASYNC_JOB 132 
#define  SSL_ERROR_WANT_READ 131 
#define  SSL_ERROR_WANT_WRITE 130 
#define  SSL_ERROR_WANT_X509_LOOKUP 129 
#define  SSL_ERROR_ZERO_RETURN 128 
 int /*<<< orphan*/  SSL_KEY_UPDATE_NOT_REQUESTED ; 
 int /*<<< orphan*/  SSL_KEY_UPDATE_REQUESTED ; 
 int /*<<< orphan*/  SSL_OP_COOKIE_EXCHANGE ; 
 int /*<<< orphan*/  SSL_OP_NO_QUERY_MTU ; 
 int SSL_READ_EARLY_DATA_ERROR ; 
 int SSL_READ_EARLY_DATA_FINISH ; 
 int SSL_RECEIVED_SHUTDOWN ; 
 int SSL_SENT_SHUTDOWN ; 
 int SSL_VERIFY_CLIENT_ONCE ; 
 int SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSL_clear (int /*<<< orphan*/ *) ; 
 int SSL_do_handshake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_SSL_CTX (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_get_early_data_status (int /*<<< orphan*/ *) ; 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_get_rbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_wbio (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_has_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_heartbeat (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_is_dtls (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_is_init_finished (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_key_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ ) ; 
 int SSL_read (int /*<<< orphan*/ *,char*,int) ; 
 int SSL_read_early_data (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  SSL_renegotiate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_accept_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_msg_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_msg_callback_arg (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SSL_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_session_id_context (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_shutdown (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_set_tlsext_debug_arg (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SSL_set_tlsext_debug_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_verify (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_trace ; 
 int SSL_verify_client_post_handshake (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_version (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_waiting_for_async (int /*<<< orphan*/ *) ; 
 int SSL_write (int /*<<< orphan*/ *,char*,unsigned int) ; 
 char* app_malloc (int,char*) ; 
 int /*<<< orphan*/  ascii2ebcdic (char*,char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ async ; 
 int /*<<< orphan*/  bio_dump_callback ; 
 scalar_t__ bio_err ; 
 scalar_t__ bio_s_msg ; 
 scalar_t__ bio_s_out ; 
 int bufsize ; 
 int /*<<< orphan*/  close_accept_socket () ; 
 int count ; 
 int /*<<< orphan*/  ctx ; 
 scalar_t__ early_data ; 
 int /*<<< orphan*/  ebcdic2ascii (char*,char*,int) ; 
 scalar_t__ enable_timeouts ; 
 int fileno_stdin () ; 
 scalar_t__ has_stdin_waiting () ; 
 int init_ssl_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_cb ; 
 int /*<<< orphan*/  openssl_fdset (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_connection_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_stats (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int raw_read_stdin (char*,int) ; 
 int /*<<< orphan*/  raw_write_stdout (char*,unsigned int) ; 
 int /*<<< orphan*/  s_brief ; 
 scalar_t__ s_crlf ; 
 scalar_t__ s_debug ; 
 int s_msg ; 
 scalar_t__ s_nbio ; 
 scalar_t__ s_nbio_test ; 
 int /*<<< orphan*/  s_quiet ; 
 scalar_t__ s_tlsextdebug ; 
 int select (int,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ socket_mtu ; 
 TYPE_1__ srp_callback_parm ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  tlsext_cb ; 
 int /*<<< orphan*/  wait_for_async (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sv_body(int s, int stype, int prot, unsigned char *context)
{
    char *buf = NULL;
    fd_set readfds;
    int ret = 1, width;
    int k, i;
    unsigned long l;
    SSL *con = NULL;
    BIO *sbio;
    struct timeval timeout;
#if !(defined(OPENSSL_SYS_WINDOWS) || defined(OPENSSL_SYS_MSDOS))
    struct timeval *timeoutp;
#endif
#ifndef OPENSSL_NO_DTLS
# ifndef OPENSSL_NO_SCTP
    int isdtls = (stype == SOCK_DGRAM || prot == IPPROTO_SCTP);
# else
    int isdtls = (stype == SOCK_DGRAM);
# endif
#endif

    buf = app_malloc(bufsize, "server buffer");
    if (s_nbio) {
        if (!BIO_socket_nbio(s, 1))
            ERR_print_errors(bio_err);
        else if (!s_quiet)
            BIO_printf(bio_err, "Turned on non blocking io\n");
    }

    con = SSL_new(ctx);
    if (con == NULL) {
        ret = -1;
        goto err;
    }

    if (s_tlsextdebug) {
        SSL_set_tlsext_debug_callback(con, tlsext_cb);
        SSL_set_tlsext_debug_arg(con, bio_s_out);
    }

    if (context != NULL
        && !SSL_set_session_id_context(con, context,
                                       strlen((char *)context))) {
        BIO_printf(bio_err, "Error setting session id context\n");
        ret = -1;
        goto err;
    }

    if (!SSL_clear(con)) {
        BIO_printf(bio_err, "Error clearing SSL connection\n");
        ret = -1;
        goto err;
    }
#ifndef OPENSSL_NO_DTLS
    if (isdtls) {
# ifndef OPENSSL_NO_SCTP
        if (prot == IPPROTO_SCTP)
            sbio = BIO_new_dgram_sctp(s, BIO_NOCLOSE);
        else
# endif
            sbio = BIO_new_dgram(s, BIO_NOCLOSE);

        if (enable_timeouts) {
            timeout.tv_sec = 0;
            timeout.tv_usec = DGRAM_RCV_TIMEOUT;
            BIO_ctrl(sbio, BIO_CTRL_DGRAM_SET_RECV_TIMEOUT, 0, &timeout);

            timeout.tv_sec = 0;
            timeout.tv_usec = DGRAM_SND_TIMEOUT;
            BIO_ctrl(sbio, BIO_CTRL_DGRAM_SET_SEND_TIMEOUT, 0, &timeout);
        }

        if (socket_mtu) {
            if (socket_mtu < DTLS_get_link_min_mtu(con)) {
                BIO_printf(bio_err, "MTU too small. Must be at least %ld\n",
                           DTLS_get_link_min_mtu(con));
                ret = -1;
                BIO_free(sbio);
                goto err;
            }
            SSL_set_options(con, SSL_OP_NO_QUERY_MTU);
            if (!DTLS_set_link_mtu(con, socket_mtu)) {
                BIO_printf(bio_err, "Failed to set MTU\n");
                ret = -1;
                BIO_free(sbio);
                goto err;
            }
        } else
            /* want to do MTU discovery */
            BIO_ctrl(sbio, BIO_CTRL_DGRAM_MTU_DISCOVER, 0, NULL);

# ifndef OPENSSL_NO_SCTP
        if (prot != IPPROTO_SCTP)
# endif
            /* Turn on cookie exchange. Not necessary for SCTP */
            SSL_set_options(con, SSL_OP_COOKIE_EXCHANGE);
    } else
#endif
        sbio = BIO_new_socket(s, BIO_NOCLOSE);

    if (sbio == NULL) {
        BIO_printf(bio_err, "Unable to create BIO\n");
        ERR_print_errors(bio_err);
        goto err;
    }

    if (s_nbio_test) {
        BIO *test;

        test = BIO_new(BIO_f_nbio_test());
        sbio = BIO_push(test, sbio);
    }

    SSL_set_bio(con, sbio, sbio);
    SSL_set_accept_state(con);
    /* SSL_set_fd(con,s); */

    if (s_debug) {
        BIO_set_callback(SSL_get_rbio(con), bio_dump_callback);
        BIO_set_callback_arg(SSL_get_rbio(con), (char *)bio_s_out);
    }
    if (s_msg) {
#ifndef OPENSSL_NO_SSL_TRACE
        if (s_msg == 2)
            SSL_set_msg_callback(con, SSL_trace);
        else
#endif
            SSL_set_msg_callback(con, msg_cb);
        SSL_set_msg_callback_arg(con, bio_s_msg ? bio_s_msg : bio_s_out);
    }

    if (s_tlsextdebug) {
        SSL_set_tlsext_debug_callback(con, tlsext_cb);
        SSL_set_tlsext_debug_arg(con, bio_s_out);
    }

    if (early_data) {
        int write_header = 1, edret = SSL_READ_EARLY_DATA_ERROR;
        size_t readbytes;

        while (edret != SSL_READ_EARLY_DATA_FINISH) {
            for (;;) {
                edret = SSL_read_early_data(con, buf, bufsize, &readbytes);
                if (edret != SSL_READ_EARLY_DATA_ERROR)
                    break;

                switch (SSL_get_error(con, 0)) {
                case SSL_ERROR_WANT_WRITE:
                case SSL_ERROR_WANT_ASYNC:
                case SSL_ERROR_WANT_READ:
                    /* Just keep trying - busy waiting */
                    continue;
                default:
                    BIO_printf(bio_err, "Error reading early data\n");
                    ERR_print_errors(bio_err);
                    goto err;
                }
            }
            if (readbytes > 0) {
                if (write_header) {
                    BIO_printf(bio_s_out, "Early data received:\n");
                    write_header = 0;
                }
                raw_write_stdout(buf, (unsigned int)readbytes);
                (void)BIO_flush(bio_s_out);
            }
        }
        if (write_header) {
            if (SSL_get_early_data_status(con) == SSL_EARLY_DATA_NOT_SENT)
                BIO_printf(bio_s_out, "No early data received\n");
            else
                BIO_printf(bio_s_out, "Early data was rejected\n");
        } else {
            BIO_printf(bio_s_out, "\nEnd of early data\n");
        }
        if (SSL_is_init_finished(con))
            print_connection_info(con);
    }

    if (fileno_stdin() > s)
        width = fileno_stdin() + 1;
    else
        width = s + 1;
    for (;;) {
        int read_from_terminal;
        int read_from_sslcon;

        read_from_terminal = 0;
        read_from_sslcon = SSL_has_pending(con)
                           || (async && SSL_waiting_for_async(con));

        if (!read_from_sslcon) {
            FD_ZERO(&readfds);
#if !defined(OPENSSL_SYS_WINDOWS) && !defined(OPENSSL_SYS_MSDOS)
            openssl_fdset(fileno_stdin(), &readfds);
#endif
            openssl_fdset(s, &readfds);
            /*
             * Note: under VMS with SOCKETSHR the second parameter is
             * currently of type (int *) whereas under other systems it is
             * (void *) if you don't have a cast it will choke the compiler:
             * if you do have a cast then you can either go for (int *) or
             * (void *).
             */
#if defined(OPENSSL_SYS_WINDOWS) || defined(OPENSSL_SYS_MSDOS)
            /*
             * Under DOS (non-djgpp) and Windows we can't select on stdin:
             * only on sockets. As a workaround we timeout the select every
             * second and check for any keypress. In a proper Windows
             * application we wouldn't do this because it is inefficient.
             */
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;
            i = select(width, (void *)&readfds, NULL, NULL, &timeout);
            if (has_stdin_waiting())
                read_from_terminal = 1;
            if ((i < 0) || (!i && !read_from_terminal))
                continue;
#else
            if (SSL_is_dtls(con) && DTLSv1_get_timeout(con, &timeout))
                timeoutp = &timeout;
            else
                timeoutp = NULL;

            i = select(width, (void *)&readfds, NULL, NULL, timeoutp);

            if ((SSL_is_dtls(con)) && DTLSv1_handle_timeout(con) > 0)
                BIO_printf(bio_err, "TIMEOUT occurred\n");

            if (i <= 0)
                continue;
            if (FD_ISSET(fileno_stdin(), &readfds))
                read_from_terminal = 1;
#endif
            if (FD_ISSET(s, &readfds))
                read_from_sslcon = 1;
        }
        if (read_from_terminal) {
            if (s_crlf) {
                int j, lf_num;

                i = raw_read_stdin(buf, bufsize / 2);
                lf_num = 0;
                /* both loops are skipped when i <= 0 */
                for (j = 0; j < i; j++)
                    if (buf[j] == '\n')
                        lf_num++;
                for (j = i - 1; j >= 0; j--) {
                    buf[j + lf_num] = buf[j];
                    if (buf[j] == '\n') {
                        lf_num--;
                        i++;
                        buf[j + lf_num] = '\r';
                    }
                }
                assert(lf_num == 0);
            } else {
                i = raw_read_stdin(buf, bufsize);
            }

            if (!s_quiet && !s_brief) {
                if ((i <= 0) || (buf[0] == 'Q')) {
                    BIO_printf(bio_s_out, "DONE\n");
                    (void)BIO_flush(bio_s_out);
                    BIO_closesocket(s);
                    close_accept_socket();
                    ret = -11;
                    goto err;
                }
                if ((i <= 0) || (buf[0] == 'q')) {
                    BIO_printf(bio_s_out, "DONE\n");
                    (void)BIO_flush(bio_s_out);
                    if (SSL_version(con) != DTLS1_VERSION)
                        BIO_closesocket(s);
                    /*
                     * close_accept_socket(); ret= -11;
                     */
                    goto err;
                }
#ifndef OPENSSL_NO_HEARTBEATS
                if ((buf[0] == 'B') && ((buf[1] == '\n') || (buf[1] == '\r'))) {
                    BIO_printf(bio_err, "HEARTBEATING\n");
                    SSL_heartbeat(con);
                    i = 0;
                    continue;
                }
#endif
                if ((buf[0] == 'r') && ((buf[1] == '\n') || (buf[1] == '\r'))) {
                    SSL_renegotiate(con);
                    i = SSL_do_handshake(con);
                    printf("SSL_do_handshake -> %d\n", i);
                    i = 0;      /* 13; */
                    continue;
                }
                if ((buf[0] == 'R') && ((buf[1] == '\n') || (buf[1] == '\r'))) {
                    SSL_set_verify(con,
                                   SSL_VERIFY_PEER | SSL_VERIFY_CLIENT_ONCE,
                                   NULL);
                    SSL_renegotiate(con);
                    i = SSL_do_handshake(con);
                    printf("SSL_do_handshake -> %d\n", i);
                    i = 0;      /* 13; */
                    continue;
                }
                if ((buf[0] == 'K' || buf[0] == 'k')
                        && ((buf[1] == '\n') || (buf[1] == '\r'))) {
                    SSL_key_update(con, buf[0] == 'K' ?
                                        SSL_KEY_UPDATE_REQUESTED
                                        : SSL_KEY_UPDATE_NOT_REQUESTED);
                    i = SSL_do_handshake(con);
                    printf("SSL_do_handshake -> %d\n", i);
                    i = 0;
                    continue;
                }
                if (buf[0] == 'c' && ((buf[1] == '\n') || (buf[1] == '\r'))) {
                    SSL_set_verify(con, SSL_VERIFY_PEER, NULL);
                    i = SSL_verify_client_post_handshake(con);
                    if (i == 0) {
                        printf("Failed to initiate request\n");
                        ERR_print_errors(bio_err);
                    } else {
                        i = SSL_do_handshake(con);
                        printf("SSL_do_handshake -> %d\n", i);
                        i = 0;
                    }
                    continue;
                }
                if (buf[0] == 'P') {
                    static const char *str = "Lets print some clear text\n";
                    BIO_write(SSL_get_wbio(con), str, strlen(str));
                }
                if (buf[0] == 'S') {
                    print_stats(bio_s_out, SSL_get_SSL_CTX(con));
                }
            }
#ifdef CHARSET_EBCDIC
            ebcdic2ascii(buf, buf, i);
#endif
            l = k = 0;
            for (;;) {
                /* should do a select for the write */
#ifdef RENEG
                static count = 0;
                if (++count == 100) {
                    count = 0;
                    SSL_renegotiate(con);
                }
#endif
                k = SSL_write(con, &(buf[l]), (unsigned int)i);
#ifndef OPENSSL_NO_SRP
                while (SSL_get_error(con, k) == SSL_ERROR_WANT_X509_LOOKUP) {
                    BIO_printf(bio_s_out, "LOOKUP renego during write\n");
                    SRP_user_pwd_free(srp_callback_parm.user);
                    srp_callback_parm.user =
                        SRP_VBASE_get1_by_user(srp_callback_parm.vb,
                                               srp_callback_parm.login);
                    if (srp_callback_parm.user)
                        BIO_printf(bio_s_out, "LOOKUP done %s\n",
                                   srp_callback_parm.user->info);
                    else
                        BIO_printf(bio_s_out, "LOOKUP not successful\n");
                    k = SSL_write(con, &(buf[l]), (unsigned int)i);
                }
#endif
                switch (SSL_get_error(con, k)) {
                case SSL_ERROR_NONE:
                    break;
                case SSL_ERROR_WANT_ASYNC:
                    BIO_printf(bio_s_out, "Write BLOCK (Async)\n");
                    (void)BIO_flush(bio_s_out);
                    wait_for_async(con);
                    break;
                case SSL_ERROR_WANT_WRITE:
                case SSL_ERROR_WANT_READ:
                case SSL_ERROR_WANT_X509_LOOKUP:
                    BIO_printf(bio_s_out, "Write BLOCK\n");
                    (void)BIO_flush(bio_s_out);
                    break;
                case SSL_ERROR_WANT_ASYNC_JOB:
                    /*
                     * This shouldn't ever happen in s_server. Treat as an error
                     */
                case SSL_ERROR_SYSCALL:
                case SSL_ERROR_SSL:
                    BIO_printf(bio_s_out, "ERROR\n");
                    (void)BIO_flush(bio_s_out);
                    ERR_print_errors(bio_err);
                    ret = 1;
                    goto err;
                    /* break; */
                case SSL_ERROR_ZERO_RETURN:
                    BIO_printf(bio_s_out, "DONE\n");
                    (void)BIO_flush(bio_s_out);
                    ret = 1;
                    goto err;
                }
                if (k > 0) {
                    l += k;
                    i -= k;
                }
                if (i <= 0)
                    break;
            }
        }
        if (read_from_sslcon) {
            /*
             * init_ssl_connection handles all async events itself so if we're
             * waiting for async then we shouldn't go back into
             * init_ssl_connection
             */
            if ((!async || !SSL_waiting_for_async(con))
                    && !SSL_is_init_finished(con)) {
                i = init_ssl_connection(con);

                if (i < 0) {
                    ret = 0;
                    goto err;
                } else if (i == 0) {
                    ret = 1;
                    goto err;
                }
            } else {
 again:
                i = SSL_read(con, (char *)buf, bufsize);
#ifndef OPENSSL_NO_SRP
                while (SSL_get_error(con, i) == SSL_ERROR_WANT_X509_LOOKUP) {
                    BIO_printf(bio_s_out, "LOOKUP renego during read\n");
                    SRP_user_pwd_free(srp_callback_parm.user);
                    srp_callback_parm.user =
                        SRP_VBASE_get1_by_user(srp_callback_parm.vb,
                                               srp_callback_parm.login);
                    if (srp_callback_parm.user)
                        BIO_printf(bio_s_out, "LOOKUP done %s\n",
                                   srp_callback_parm.user->info);
                    else
                        BIO_printf(bio_s_out, "LOOKUP not successful\n");
                    i = SSL_read(con, (char *)buf, bufsize);
                }
#endif
                switch (SSL_get_error(con, i)) {
                case SSL_ERROR_NONE:
#ifdef CHARSET_EBCDIC
                    ascii2ebcdic(buf, buf, i);
#endif
                    raw_write_stdout(buf, (unsigned int)i);
                    (void)BIO_flush(bio_s_out);
                    if (SSL_has_pending(con))
                        goto again;
                    break;
                case SSL_ERROR_WANT_ASYNC:
                    BIO_printf(bio_s_out, "Read BLOCK (Async)\n");
                    (void)BIO_flush(bio_s_out);
                    wait_for_async(con);
                    break;
                case SSL_ERROR_WANT_WRITE:
                case SSL_ERROR_WANT_READ:
                    BIO_printf(bio_s_out, "Read BLOCK\n");
                    (void)BIO_flush(bio_s_out);
                    break;
                case SSL_ERROR_WANT_ASYNC_JOB:
                    /*
                     * This shouldn't ever happen in s_server. Treat as an error
                     */
                case SSL_ERROR_SYSCALL:
                case SSL_ERROR_SSL:
                    BIO_printf(bio_s_out, "ERROR\n");
                    (void)BIO_flush(bio_s_out);
                    ERR_print_errors(bio_err);
                    ret = 1;
                    goto err;
                case SSL_ERROR_ZERO_RETURN:
                    BIO_printf(bio_s_out, "DONE\n");
                    (void)BIO_flush(bio_s_out);
                    ret = 1;
                    goto err;
                }
            }
        }
    }
 err:
    if (con != NULL) {
        BIO_printf(bio_s_out, "shutting down SSL\n");
        SSL_set_shutdown(con, SSL_SENT_SHUTDOWN | SSL_RECEIVED_SHUTDOWN);
        SSL_free(con);
    }
    BIO_printf(bio_s_out, "CONNECTION CLOSED\n");
    OPENSSL_clear_free(buf, bufsize);
    return ret;
}