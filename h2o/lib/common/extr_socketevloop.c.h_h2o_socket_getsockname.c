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
struct st_h2o_evloop_socket_t {int /*<<< orphan*/  fd; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  h2o_socket_t ;

/* Variables and functions */
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

socklen_t h2o_socket_getsockname(h2o_socket_t *_sock, struct sockaddr *sa)
{
    struct st_h2o_evloop_socket_t *sock = (void *)_sock;
    socklen_t len = sizeof(struct sockaddr_storage);
    if (getsockname(sock->fd, sa, &len) != 0)
        return 0;
    return len;
}