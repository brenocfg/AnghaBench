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
struct st_h2o_evloop_socket_t {int /*<<< orphan*/  super; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_socket_cb ;
typedef  int /*<<< orphan*/  h2o_loop_t ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  H2O_SOCKET_FLAG_IS_CONNECTING ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int cloexec_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 struct st_h2o_evloop_socket_t* create_socket_set_nodelay (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_notify_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

h2o_socket_t *h2o_socket_connect(h2o_loop_t *loop, struct sockaddr *addr, socklen_t addrlen, h2o_socket_cb cb)
{
    int fd;
    struct st_h2o_evloop_socket_t *sock;

    if ((fd = cloexec_socket(addr->sa_family, SOCK_STREAM, 0)) == -1)
        return NULL;
    fcntl(fd, F_SETFL, O_NONBLOCK);
    if (!(connect(fd, addr, addrlen) == 0 || errno == EINPROGRESS)) {
        close(fd);
        return NULL;
    }

    sock = create_socket_set_nodelay(loop, fd, H2O_SOCKET_FLAG_IS_CONNECTING);
    h2o_socket_notify_write(&sock->super, cb);
    return &sock->super;
}