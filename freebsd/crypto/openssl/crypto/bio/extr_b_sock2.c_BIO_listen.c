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
typedef  int /*<<< orphan*/  socktype ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  BIO_ADDR ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ BIO_ADDR_family (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BIO_F_BIO_LISTEN ; 
 int /*<<< orphan*/  BIO_R_GETTING_SOCKTYPE ; 
 int /*<<< orphan*/  BIO_R_INVALID_SOCKET ; 
 int /*<<< orphan*/  BIO_R_LISTEN_V6_ONLY ; 
 int /*<<< orphan*/  BIO_R_UNABLE_TO_KEEPALIVE ; 
 int /*<<< orphan*/  BIO_R_UNABLE_TO_LISTEN_SOCKET ; 
 int /*<<< orphan*/  BIO_R_UNABLE_TO_NODELAY ; 
 int BIO_SOCK_KEEPALIVE ; 
 int BIO_SOCK_NODELAY ; 
 int BIO_SOCK_NONBLOCK ; 
 int BIO_SOCK_V6_ONLY ; 
 int /*<<< orphan*/  BIO_bind (int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  BIO_socket_nbio (int,int) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  MAX_LISTEN ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int /*<<< orphan*/  SYS_F_GETSOCKOPT ; 
 int /*<<< orphan*/  SYS_F_LISTEN ; 
 int /*<<< orphan*/  SYS_F_SETSOCKOPT ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  get_last_socket_error () ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int*) ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 

int BIO_listen(int sock, const BIO_ADDR *addr, int options)
{
    int on = 1;
    int socktype;
    socklen_t socktype_len = sizeof(socktype);

    if (sock == -1) {
        BIOerr(BIO_F_BIO_LISTEN, BIO_R_INVALID_SOCKET);
        return 0;
    }

    if (getsockopt(sock, SOL_SOCKET, SO_TYPE,
                   (void *)&socktype, &socktype_len) != 0
        || socktype_len != sizeof(socktype)) {
        SYSerr(SYS_F_GETSOCKOPT, get_last_socket_error());
        BIOerr(BIO_F_BIO_LISTEN, BIO_R_GETTING_SOCKTYPE);
        return 0;
    }

    if (!BIO_socket_nbio(sock, (options & BIO_SOCK_NONBLOCK) != 0))
        return 0;

    if (options & BIO_SOCK_KEEPALIVE) {
        if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,
                       (const void *)&on, sizeof(on)) != 0) {
            SYSerr(SYS_F_SETSOCKOPT, get_last_socket_error());
            BIOerr(BIO_F_BIO_LISTEN, BIO_R_UNABLE_TO_KEEPALIVE);
            return 0;
        }
    }

    if (options & BIO_SOCK_NODELAY) {
        if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
                       (const void *)&on, sizeof(on)) != 0) {
            SYSerr(SYS_F_SETSOCKOPT, get_last_socket_error());
            BIOerr(BIO_F_BIO_LISTEN, BIO_R_UNABLE_TO_NODELAY);
            return 0;
        }
    }

# ifdef IPV6_V6ONLY
    if (BIO_ADDR_family(addr) == AF_INET6) {
        /*
         * Note: Windows default of IPV6_V6ONLY is ON, and Linux is OFF.
         * Therefore we always have to use setsockopt here.
         */
        on = options & BIO_SOCK_V6_ONLY ? 1 : 0;
        if (setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY,
                       (const void *)&on, sizeof(on)) != 0) {
            SYSerr(SYS_F_SETSOCKOPT, get_last_socket_error());
            BIOerr(BIO_F_BIO_LISTEN, BIO_R_LISTEN_V6_ONLY);
            return 0;
        }
    }
# endif

    if (!BIO_bind(sock, addr, options))
        return 0;

    if (socktype != SOCK_DGRAM && listen(sock, MAX_LISTEN) == -1) {
        SYSerr(SYS_F_LISTEN, get_last_socket_error());
        BIOerr(BIO_F_BIO_LISTEN, BIO_R_UNABLE_TO_LISTEN_SOCKET);
        return 0;
    }

    return 1;
}