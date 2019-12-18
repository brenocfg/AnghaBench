#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bai_family; int bai_socktype; int /*<<< orphan*/ * bai_addr; int /*<<< orphan*/ * bai_next; scalar_t__ bai_protocol; } ;
typedef  TYPE_1__ BIO_ADDRINFO ;
typedef  int /*<<< orphan*/  BIO_ADDR ;

/* Variables and functions */
 int AF_UNIX ; 
 int /*<<< orphan*/  BIO_ADDRINFO_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * BIO_ADDR_new () ; 
 int /*<<< orphan*/  BIO_ADDR_rawmake (int /*<<< orphan*/ *,int,void const*,size_t,unsigned short) ; 
 int /*<<< orphan*/ * BIO_ADDR_sockaddr_noconst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_F_ADDRINFO_WRAP ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 

__attribute__((used)) static int addrinfo_wrap(int family, int socktype,
                         const void *where, size_t wherelen,
                         unsigned short port,
                         BIO_ADDRINFO **bai)
{
    if ((*bai = OPENSSL_zalloc(sizeof(**bai))) == NULL) {
        BIOerr(BIO_F_ADDRINFO_WRAP, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    (*bai)->bai_family = family;
    (*bai)->bai_socktype = socktype;
    if (socktype == SOCK_STREAM)
        (*bai)->bai_protocol = IPPROTO_TCP;
    if (socktype == SOCK_DGRAM)
        (*bai)->bai_protocol = IPPROTO_UDP;
#ifdef AF_UNIX
    if (family == AF_UNIX)
        (*bai)->bai_protocol = 0;
#endif
    {
        /* Magic: We know that BIO_ADDR_sockaddr_noconst is really
           just an advanced cast of BIO_ADDR* to struct sockaddr *
           by the power of union, so while it may seem that we're
           creating a memory leak here, we are not.  It will be
           all right. */
        BIO_ADDR *addr = BIO_ADDR_new();
        if (addr != NULL) {
            BIO_ADDR_rawmake(addr, family, where, wherelen, port);
            (*bai)->bai_addr = BIO_ADDR_sockaddr_noconst(addr);
        }
    }
    (*bai)->bai_next = NULL;
    if ((*bai)->bai_addr == NULL) {
        BIO_ADDRINFO_free(*bai);
        *bai = NULL;
        return 0;
    }
    return 1;
}