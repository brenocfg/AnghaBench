#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sin6_port; } ;
struct TYPE_4__ {scalar_t__ sin_port; } ;
struct TYPE_6__ {int sa_family; } ;
union sockaddr_union {TYPE_2__ in6; TYPE_1__ in4; TYPE_3__ sa; } ;
typedef  scalar_t__ uint16_t ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sockaddr ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int EINVAL ; 
 int errno ; 
 scalar_t__ getsockname (int,TYPE_3__*,int*) ; 
 scalar_t__ htons (scalar_t__) ; 
 int /*<<< orphan*/  memset (union sockaddr_union*,int /*<<< orphan*/ ,int) ; 
 int sd_is_socket_internal (int,int,int) ; 

int sd_is_socket_inet(int fd, int family, int type, int listening, uint16_t port) {
    union sockaddr_union sockaddr;
    socklen_t l;
    int r;

    if (family != 0 && family != AF_INET && family != AF_INET6)
        return -EINVAL;

    if ((r = sd_is_socket_internal(fd, type, listening)) <= 0)
        return r;

    memset(&sockaddr, 0, sizeof(sockaddr));
    l = sizeof(sockaddr);

    if (getsockname(fd, &sockaddr.sa, &l) < 0)
        return -errno;

    if (l < sizeof(sa_family_t))
        return -EINVAL;

    if (sockaddr.sa.sa_family != AF_INET &&
        sockaddr.sa.sa_family != AF_INET6)
        return 0;

    if (family > 0)
        if (sockaddr.sa.sa_family != family)
            return 0;

    if (port > 0) {
        if (sockaddr.sa.sa_family == AF_INET) {
            if (l < sizeof(struct sockaddr_in))
                return -EINVAL;

            return htons(port) == sockaddr.in4.sin_port;
        } else {
            if (l < sizeof(struct sockaddr_in6))
                return -EINVAL;

            return htons(port) == sockaddr.in6.sin6_port;
        }
    }

    return 1;
}