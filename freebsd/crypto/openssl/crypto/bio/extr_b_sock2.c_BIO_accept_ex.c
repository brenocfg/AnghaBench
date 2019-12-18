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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  BIO_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ADDR_sockaddr_noconst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_F_BIO_ACCEPT_EX ; 
 int /*<<< orphan*/  BIO_R_ACCEPT_ERROR ; 
 int BIO_SOCK_NONBLOCK ; 
 int /*<<< orphan*/  BIO_sock_should_retry (int) ; 
 int /*<<< orphan*/  BIO_socket_nbio (int,int) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INVALID_SOCKET ; 
 int /*<<< orphan*/  SYS_F_ACCEPT ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int accept (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  get_last_socket_error () ; 

int BIO_accept_ex(int accept_sock, BIO_ADDR *addr_, int options)
{
    socklen_t len;
    int accepted_sock;
    BIO_ADDR locaddr;
    BIO_ADDR *addr = addr_ == NULL ? &locaddr : addr_;

    len = sizeof(*addr);
    accepted_sock = accept(accept_sock,
                           BIO_ADDR_sockaddr_noconst(addr), &len);
    if (accepted_sock == -1) {
        if (!BIO_sock_should_retry(accepted_sock)) {
            SYSerr(SYS_F_ACCEPT, get_last_socket_error());
            BIOerr(BIO_F_BIO_ACCEPT_EX, BIO_R_ACCEPT_ERROR);
        }
        return INVALID_SOCKET;
    }

    if (!BIO_socket_nbio(accepted_sock, (options & BIO_SOCK_NONBLOCK) != 0)) {
        closesocket(accepted_sock);
        return INVALID_SOCKET;
    }

    return accepted_sock;
}