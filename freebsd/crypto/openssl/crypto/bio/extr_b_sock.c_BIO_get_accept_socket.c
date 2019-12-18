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
typedef  int /*<<< orphan*/  BIO_ADDRINFO ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  BIO_ADDRINFO_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_protocol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_socktype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_LOOKUP_SERVER ; 
 int /*<<< orphan*/  BIO_PARSE_PRIO_SERV ; 
 int /*<<< orphan*/  BIO_SOCK_REUSEADDR ; 
 int /*<<< orphan*/  BIO_closesocket (int) ; 
 int /*<<< orphan*/  BIO_listen (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_lookup (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  BIO_parse_hostserv (char*,char**,char**,int /*<<< orphan*/ ) ; 
 int BIO_sock_init () ; 
 int BIO_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INVALID_SOCKET ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 

int BIO_get_accept_socket(char *host, int bind_mode)
{
    int s = INVALID_SOCKET;
    char *h = NULL, *p = NULL;
    BIO_ADDRINFO *res = NULL;

    if (!BIO_parse_hostserv(host, &h, &p, BIO_PARSE_PRIO_SERV))
        return INVALID_SOCKET;

    if (BIO_sock_init() != 1)
        return INVALID_SOCKET;

    if (BIO_lookup(h, p, BIO_LOOKUP_SERVER, AF_UNSPEC, SOCK_STREAM, &res) != 0)
        goto err;

    if ((s = BIO_socket(BIO_ADDRINFO_family(res), BIO_ADDRINFO_socktype(res),
                        BIO_ADDRINFO_protocol(res), 0)) == INVALID_SOCKET) {
        s = INVALID_SOCKET;
        goto err;
    }

    if (!BIO_listen(s, BIO_ADDRINFO_address(res),
                    bind_mode ? BIO_SOCK_REUSEADDR : 0)) {
        BIO_closesocket(s);
        s = INVALID_SOCKET;
    }

 err:
    BIO_ADDRINFO_free(res);
    OPENSSL_free(h);
    OPENSSL_free(p);

    return s;
}