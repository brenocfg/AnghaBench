#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 size_t SIZE_MAX ; 
 scalar_t__ getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int htonl (int /*<<< orphan*/ ) ; 
 size_t sprintf (char*,char*,int,int,int,int) ; 
 size_t strlen (char*) ; 

size_t h2o_socket_getnumerichost(struct sockaddr *sa, socklen_t salen, char *buf)
{
    if (sa->sa_family == AF_INET) {
        /* fast path for IPv4 addresses */
        struct sockaddr_in *sin = (void *)sa;
        uint32_t addr;
        addr = htonl(sin->sin_addr.s_addr);
        return sprintf(buf, "%d.%d.%d.%d", addr >> 24, (addr >> 16) & 255, (addr >> 8) & 255, addr & 255);
    }

    if (getnameinfo(sa, salen, buf, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) != 0)
        return SIZE_MAX;
    return strlen(buf);
}