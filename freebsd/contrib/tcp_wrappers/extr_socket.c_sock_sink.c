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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

__attribute__((used)) static void sock_sink(int fd)
{
    char    buf[BUFSIZ];
#ifdef INET6
    struct sockaddr_storage sin;
#else
    struct sockaddr_in sin;
#endif
    int     size = sizeof(sin);

    /*
     * Eat up the not-yet received datagram. Some systems insist on a
     * non-zero source address argument in the recvfrom() call below.
     */

    (void) recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *) & sin, &size);
}