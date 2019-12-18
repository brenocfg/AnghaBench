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
struct st_h2o_evloop_socket_t {int fd; int /*<<< orphan*/  _flags; } ;
typedef  int /*<<< orphan*/  h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SOCKET_FLAG_IS_DISPOSED ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  evloop_do_on_socket_close (struct st_h2o_evloop_socket_t*) ; 
 int /*<<< orphan*/  link_to_statechanged (struct st_h2o_evloop_socket_t*) ; 
 int /*<<< orphan*/  wreq_free_buffer_if_allocated (struct st_h2o_evloop_socket_t*) ; 

void do_dispose_socket(h2o_socket_t *_sock)
{
    struct st_h2o_evloop_socket_t *sock = (struct st_h2o_evloop_socket_t *)_sock;

    evloop_do_on_socket_close(sock);
    wreq_free_buffer_if_allocated(sock);
    if (sock->fd != -1) {
        close(sock->fd);
        sock->fd = -1;
    }
    sock->_flags = H2O_SOCKET_FLAG_IS_DISPOSED;
    link_to_statechanged(sock);
}