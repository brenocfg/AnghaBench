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
struct st_h2o_evloop_socket_t {int dummy; } ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  h2o_evloop_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 struct st_h2o_evloop_socket_t* create_socket (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static struct st_h2o_evloop_socket_t *create_socket_set_nodelay(h2o_evloop_t *loop, int fd, int flags)
{
    /* ignore errors returned by setsockopt; fd is not restricted to TCP sockets (could be a unix-domain socket for example) */
    int on = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));
    return create_socket(loop, fd, flags);
}