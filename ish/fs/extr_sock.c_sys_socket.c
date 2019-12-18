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
typedef  int /*<<< orphan*/  one ;
typedef  scalar_t__ int_t ;
typedef  scalar_t__ fd_t ;
typedef  int /*<<< orphan*/  dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET_ ; 
 int /*<<< orphan*/  IPPROTO_ICMP ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int /*<<< orphan*/  IP_STRIPHDR ; 
 int /*<<< orphan*/  SOCK_DGRAM_ ; 
 int /*<<< orphan*/  SOCK_RAW_ ; 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _EINVAL ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno_map () ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int sock_family_to_real (int /*<<< orphan*/ ) ; 
 scalar_t__ sock_fd_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sock_type_to_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 

int_t sys_socket(dword_t domain, dword_t type, dword_t protocol) {
    STRACE("socket(%d, %d, %d)", domain, type, protocol);
    int real_domain = sock_family_to_real(domain);
    if (real_domain < 0)
        return _EINVAL;
    int real_type = sock_type_to_real(type, protocol);
    if (real_type < 0)
        return _EINVAL;

    // this hack makes mtr work
    if (type == SOCK_RAW_ && protocol == IPPROTO_RAW)
        protocol = IPPROTO_ICMP;

    int sock = socket(real_domain, real_type, protocol);
    if (sock < 0)
        return errno_map();

#ifdef __APPLE__
    if (domain == AF_INET_ && type == SOCK_DGRAM_) {
        // in some cases, such as ICMP, datagram sockets on mac can default to
        // including the IP header like raw sockets
        int one = 1;
        setsockopt(sock, IPPROTO_IP, IP_STRIPHDR, &one, sizeof(one));
    }
#endif

    fd_t f = sock_fd_create(sock, domain, type, protocol);
    if (f < 0)
        close(sock);
    return f;
}