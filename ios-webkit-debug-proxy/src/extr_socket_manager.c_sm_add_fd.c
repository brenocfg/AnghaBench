#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sm_t ;
typedef  int /*<<< orphan*/  sm_status ;
typedef  TYPE_2__* sm_private_t ;
struct TYPE_6__ {int max_fd; int /*<<< orphan*/  server_fds; int /*<<< orphan*/  tmp_fail_fds; int /*<<< orphan*/  tmp_recv_fds; int /*<<< orphan*/  tmp_send_fds; int /*<<< orphan*/  recv_fds; int /*<<< orphan*/  send_fds; int /*<<< orphan*/  all_fds; int /*<<< orphan*/  fd_to_ssl; int /*<<< orphan*/  fd_to_value; } ;
struct TYPE_5__ {TYPE_2__* private_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ ) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HT_KEY (int) ; 
 int /*<<< orphan*/  SM_ERROR ; 
 int /*<<< orphan*/  SM_SUCCESS ; 
 scalar_t__ ht_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sm_on_debug (TYPE_1__*,char*,char*,int) ; 

sm_status sm_add_fd(sm_t self, int fd, void *ssl_session, void *value,
    bool is_server) {
  sm_private_t my = self->private_state;
  if (FD_ISSET(fd, my->all_fds)) {
    return SM_ERROR;
  }
  if (ht_put(my->fd_to_value, HT_KEY(fd), value)) {
    // The above FD_ISSET(..master..) should prevent this
    return SM_ERROR;
  }
  if (ssl_session != NULL && ht_put(my->fd_to_ssl, HT_KEY(fd), ssl_session)) {
    return SM_ERROR;
  }
  // is_server == getsockopt(..., SO_ACCEPTCONN, ...)?
  sm_on_debug(self, "ss.add%s_fd(%d)", (is_server ? "_server" : ""), fd);
  FD_SET(fd, my->all_fds);
  FD_CLR(fd, my->send_fds); // only set if blocked
  FD_SET(fd, my->recv_fds);
  FD_CLR(fd, my->tmp_send_fds);
  FD_CLR(fd, my->tmp_recv_fds);
  FD_CLR(fd, my->tmp_fail_fds);
  if (is_server) {
    FD_SET(fd, my->server_fds);
  }
  if (fd > my->max_fd) {
    my->max_fd = fd;
  }
  return SM_SUCCESS;
}