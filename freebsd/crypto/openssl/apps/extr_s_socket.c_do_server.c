#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
union BIO_sock_info_u {int /*<<< orphan*/ * addr; } ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  sink ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int (* do_server_cb ) (int,int,int,unsigned char*) ;
typedef  int /*<<< orphan*/  const BIO_ADDRINFO ;
typedef  int /*<<< orphan*/  BIO_ADDR ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNIX ; 
 int AF_UNSPEC ; 
 int /*<<< orphan*/ * BIO_ADDRINFO_address (int /*<<< orphan*/  const*) ; 
 int BIO_ADDRINFO_family (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BIO_ADDRINFO_next (int /*<<< orphan*/  const*) ; 
 int BIO_ADDRINFO_protocol (int /*<<< orphan*/  const*) ; 
 int BIO_ADDRINFO_socktype (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BIO_ADDR_free (int /*<<< orphan*/ *) ; 
 char* BIO_ADDR_hostname_string (int /*<<< orphan*/ *,int) ; 
 void* BIO_ADDR_new () ; 
 int BIO_ADDR_rawport (int /*<<< orphan*/  const*) ; 
 char* BIO_ADDR_service_string (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_LOOKUP_SERVER ; 
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_SOCK_INFO_ADDRESS ; 
 int BIO_SOCK_REUSEADDR ; 
 int BIO_SOCK_V6_ONLY ; 
 int BIO_accept_ex (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_closesocket (int) ; 
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_listen (int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  BIO_lookup_ex (char const*,char const*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * BIO_new_dgram_sctp (int,int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_set_tcp_ndelay (int,int) ; 
 scalar_t__ BIO_sock_info (int,int /*<<< orphan*/ ,union BIO_sock_info_u*) ; 
 int BIO_sock_init () ; 
 scalar_t__ BIO_sock_should_retry (int) ; 
 int BIO_socket (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int INVALID_SOCKET ; 
 int IPPROTO_SCTP ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  openssl_fdset (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ourpeer ; 
 scalar_t__ readsocket (int,char*,int) ; 
 scalar_t__ select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  shutdown (int,int) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int stub1 (int,int,int,unsigned char*) ; 
 int stub2 (int,int,int,unsigned char*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

int do_server(int *accept_sock, const char *host, const char *port,
              int family, int type, int protocol, do_server_cb cb,
              unsigned char *context, int naccept, BIO *bio_s_out)
{
    int asock = 0;
    int sock;
    int i;
    BIO_ADDRINFO *res = NULL;
    const BIO_ADDRINFO *next;
    int sock_family, sock_type, sock_protocol, sock_port;
    const BIO_ADDR *sock_address;
    int sock_options = BIO_SOCK_REUSEADDR;
    int ret = 0;

    if (BIO_sock_init() != 1)
        return 0;

    if (!BIO_lookup_ex(host, port, BIO_LOOKUP_SERVER, family, type, protocol,
                       &res)) {
        ERR_print_errors(bio_err);
        return 0;
    }

    /* Admittedly, these checks are quite paranoid, we should not get
     * anything in the BIO_ADDRINFO chain that we haven't asked for */
    OPENSSL_assert((family == AF_UNSPEC || family == BIO_ADDRINFO_family(res))
                   && (type == 0 || type == BIO_ADDRINFO_socktype(res))
                   && (protocol == 0 || protocol == BIO_ADDRINFO_protocol(res)));

    sock_family = BIO_ADDRINFO_family(res);
    sock_type = BIO_ADDRINFO_socktype(res);
    sock_protocol = BIO_ADDRINFO_protocol(res);
    sock_address = BIO_ADDRINFO_address(res);
    next = BIO_ADDRINFO_next(res);
    if (sock_family == AF_INET6)
        sock_options |= BIO_SOCK_V6_ONLY;
    if (next != NULL
            && BIO_ADDRINFO_socktype(next) == sock_type
            && BIO_ADDRINFO_protocol(next) == sock_protocol) {
        if (sock_family == AF_INET
                && BIO_ADDRINFO_family(next) == AF_INET6) {
            sock_family = AF_INET6;
            sock_address = BIO_ADDRINFO_address(next);
        } else if (sock_family == AF_INET6
                   && BIO_ADDRINFO_family(next) == AF_INET) {
            sock_options &= ~BIO_SOCK_V6_ONLY;
        }
    }

    asock = BIO_socket(sock_family, sock_type, sock_protocol, 0);
    if (asock == INVALID_SOCKET
        || !BIO_listen(asock, sock_address, sock_options)) {
        BIO_ADDRINFO_free(res);
        ERR_print_errors(bio_err);
        if (asock != INVALID_SOCKET)
            BIO_closesocket(asock);
        goto end;
    }

#ifndef OPENSSL_NO_SCTP
    if (protocol == IPPROTO_SCTP) {
        /*
         * For SCTP we have to set various options on the socket prior to
         * accepting. This is done automatically by BIO_new_dgram_sctp().
         * We don't actually need the created BIO though so we free it again
         * immediately.
         */
        BIO *tmpbio = BIO_new_dgram_sctp(asock, BIO_NOCLOSE);

        if (tmpbio == NULL) {
            BIO_closesocket(asock);
            ERR_print_errors(bio_err);
            goto end;
        }
        BIO_free(tmpbio);
    }
#endif

    sock_port = BIO_ADDR_rawport(sock_address);

    BIO_ADDRINFO_free(res);
    res = NULL;

    if (sock_port == 0) {
        /* dynamically allocated port, report which one */
        union BIO_sock_info_u info;
        char *hostname = NULL;
        char *service = NULL;
        int success = 0;

        if ((info.addr = BIO_ADDR_new()) != NULL
            && BIO_sock_info(asock, BIO_SOCK_INFO_ADDRESS, &info)
            && (hostname = BIO_ADDR_hostname_string(info.addr, 1)) != NULL
            && (service = BIO_ADDR_service_string(info.addr, 1)) != NULL
            && BIO_printf(bio_s_out,
                          strchr(hostname, ':') == NULL
                          ? /* IPv4 */ "ACCEPT %s:%s\n"
                          : /* IPv6 */ "ACCEPT [%s]:%s\n",
                          hostname, service) > 0)
            success = 1;

        (void)BIO_flush(bio_s_out);
        OPENSSL_free(hostname);
        OPENSSL_free(service);
        BIO_ADDR_free(info.addr);
        if (!success) {
            BIO_closesocket(asock);
            ERR_print_errors(bio_err);
            goto end;
        }
    } else {
        (void)BIO_printf(bio_s_out, "ACCEPT\n");
        (void)BIO_flush(bio_s_out);
    }

    if (accept_sock != NULL)
        *accept_sock = asock;
    for (;;) {
        char sink[64];
        struct timeval timeout;
        fd_set readfds;

        if (type == SOCK_STREAM) {
            BIO_ADDR_free(ourpeer);
            ourpeer = BIO_ADDR_new();
            if (ourpeer == NULL) {
                BIO_closesocket(asock);
                ERR_print_errors(bio_err);
                goto end;
            }
            do {
                sock = BIO_accept_ex(asock, ourpeer, 0);
            } while (sock < 0 && BIO_sock_should_retry(sock));
            if (sock < 0) {
                ERR_print_errors(bio_err);
                BIO_closesocket(asock);
                break;
            }
            BIO_set_tcp_ndelay(sock, 1);
            i = (*cb)(sock, type, protocol, context);

            /*
             * If we ended with an alert being sent, but still with data in the
             * network buffer to be read, then calling BIO_closesocket() will
             * result in a TCP-RST being sent. On some platforms (notably
             * Windows) then this will result in the peer immediately abandoning
             * the connection including any buffered alert data before it has
             * had a chance to be read. Shutting down the sending side first,
             * and then closing the socket sends TCP-FIN first followed by
             * TCP-RST. This seems to allow the peer to read the alert data.
             */
            shutdown(sock, 1); /* SHUT_WR */
            /*
             * We just said we have nothing else to say, but it doesn't mean
             * that the other side has nothing. It's even recommended to
             * consume incoming data. [In testing context this ensures that
             * alerts are passed on...]
             */
            timeout.tv_sec = 0;
            timeout.tv_usec = 500000;  /* some extreme round-trip */
            do {
                FD_ZERO(&readfds);
                openssl_fdset(sock, &readfds);
            } while (select(sock + 1, &readfds, NULL, NULL, &timeout) > 0
                     && readsocket(sock, sink, sizeof(sink)) > 0);

            BIO_closesocket(sock);
        } else {
            i = (*cb)(asock, type, protocol, context);
        }

        if (naccept != -1)
            naccept--;
        if (i < 0 || naccept == 0) {
            BIO_closesocket(asock);
            ret = i;
            break;
        }
    }
 end:
# ifdef AF_UNIX
    if (family == AF_UNIX)
        unlink(host);
# endif
    BIO_ADDR_free(ourpeer);
    ourpeer = NULL;
    return ret;
}