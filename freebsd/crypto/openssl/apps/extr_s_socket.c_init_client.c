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
typedef  int /*<<< orphan*/  const BIO_ADDRINFO ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNIX ; 
 int AF_UNSPEC ; 
 int /*<<< orphan*/  BIO_ADDRINFO_address (int /*<<< orphan*/  const*) ; 
 int BIO_ADDRINFO_family (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BIO_ADDRINFO_next (int /*<<< orphan*/  const*) ; 
 int BIO_ADDRINFO_protocol (int /*<<< orphan*/  const*) ; 
 int BIO_ADDRINFO_socktype (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BIO_LOOKUP_CLIENT ; 
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_SOCK_NODELAY ; 
 int /*<<< orphan*/  BIO_SOCK_REUSEADDR ; 
 int /*<<< orphan*/  BIO_bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_closesocket (int) ; 
 int /*<<< orphan*/  BIO_connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int BIO_lookup_ex (char const*,char const*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * BIO_new_dgram_sctp (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char*,char const*,char*,char const*) ; 
 int BIO_sock_init () ; 
 int BIO_socket (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int INVALID_SOCKET ; 
 int IPPROTO_SCTP ; 
 int IPPROTO_TCP ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  bio_err ; 

int init_client(int *sock, const char *host, const char *port,
                const char *bindhost, const char *bindport,
                int family, int type, int protocol)
{
    BIO_ADDRINFO *res = NULL;
    BIO_ADDRINFO *bindaddr = NULL;
    const BIO_ADDRINFO *ai = NULL;
    const BIO_ADDRINFO *bi = NULL;
    int found = 0;
    int ret;

    if (BIO_sock_init() != 1)
        return 0;

    ret = BIO_lookup_ex(host, port, BIO_LOOKUP_CLIENT, family, type, protocol,
                        &res);
    if (ret == 0) {
        ERR_print_errors(bio_err);
        return 0;
    }

    if (bindhost != NULL || bindport != NULL) {
        ret = BIO_lookup_ex(bindhost, bindport, BIO_LOOKUP_CLIENT,
                            family, type, protocol, &bindaddr);
        if (ret == 0) {
            ERR_print_errors (bio_err);
            goto out;
        }
    }

    ret = 0;
    for (ai = res; ai != NULL; ai = BIO_ADDRINFO_next(ai)) {
        /* Admittedly, these checks are quite paranoid, we should not get
         * anything in the BIO_ADDRINFO chain that we haven't
         * asked for. */
        OPENSSL_assert((family == AF_UNSPEC
                        || family == BIO_ADDRINFO_family(ai))
                       && (type == 0 || type == BIO_ADDRINFO_socktype(ai))
                       && (protocol == 0
                           || protocol == BIO_ADDRINFO_protocol(ai)));

        if (bindaddr != NULL) {
            for (bi = bindaddr; bi != NULL; bi = BIO_ADDRINFO_next(bi)) {
                if (BIO_ADDRINFO_family(bi) == BIO_ADDRINFO_family(ai))
                    break;
            }
            if (bi == NULL)
                continue;
            ++found;
        }

        *sock = BIO_socket(BIO_ADDRINFO_family(ai), BIO_ADDRINFO_socktype(ai),
                           BIO_ADDRINFO_protocol(ai), 0);
        if (*sock == INVALID_SOCKET) {
            /* Maybe the kernel doesn't support the socket family, even if
             * BIO_lookup() added it in the returned result...
             */
            continue;
        }

        if (bi != NULL) {
            if (!BIO_bind(*sock, BIO_ADDRINFO_address(bi),
                          BIO_SOCK_REUSEADDR)) {
                BIO_closesocket(*sock);
                *sock = INVALID_SOCKET;
                break;
            }
        }

#ifndef OPENSSL_NO_SCTP
        if (protocol == IPPROTO_SCTP) {
            /*
             * For SCTP we have to set various options on the socket prior to
             * connecting. This is done automatically by BIO_new_dgram_sctp().
             * We don't actually need the created BIO though so we free it again
             * immediately.
             */
            BIO *tmpbio = BIO_new_dgram_sctp(*sock, BIO_NOCLOSE);

            if (tmpbio == NULL) {
                ERR_print_errors(bio_err);
                return 0;
            }
            BIO_free(tmpbio);
        }
#endif

        if (!BIO_connect(*sock, BIO_ADDRINFO_address(ai),
                         protocol == IPPROTO_TCP ? BIO_SOCK_NODELAY : 0)) {
            BIO_closesocket(*sock);
            *sock = INVALID_SOCKET;
            continue;
        }

        /* Success, don't try any more addresses */
        break;
    }

    if (*sock == INVALID_SOCKET) {
        if (bindaddr != NULL && !found) {
            BIO_printf(bio_err, "Can't bind %saddress for %s%s%s\n",
                       BIO_ADDRINFO_family(res) == AF_INET6 ? "IPv6 " :
                       BIO_ADDRINFO_family(res) == AF_INET ? "IPv4 " :
                       BIO_ADDRINFO_family(res) == AF_UNIX ? "unix " : "",
                       bindhost != NULL ? bindhost : "",
                       bindport != NULL ? ":" : "",
                       bindport != NULL ? bindport : "");
            ERR_clear_error();
            ret = 0;
        }
        ERR_print_errors(bio_err);
    } else {
        /* Remove any stale errors from previous connection attempts */
        ERR_clear_error();
        ret = 1;
    }
out:
    if (bindaddr != NULL) {
        BIO_ADDRINFO_free (bindaddr);
    }
    BIO_ADDRINFO_free(res);
    return ret;
}