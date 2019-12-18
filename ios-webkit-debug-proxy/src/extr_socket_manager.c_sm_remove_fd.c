#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sm_t ;
typedef  int /*<<< orphan*/  sm_status ;
typedef  TYPE_2__* sm_sendq_t ;
typedef  TYPE_3__* sm_private_t ;
struct TYPE_10__ {int max_fd; int /*<<< orphan*/  fd_to_sendq; int /*<<< orphan*/  all_fds; int /*<<< orphan*/  tmp_fail_fds; int /*<<< orphan*/  tmp_recv_fds; int /*<<< orphan*/  tmp_send_fds; int /*<<< orphan*/  recv_fds; int /*<<< orphan*/  send_fds; int /*<<< orphan*/  server_fds; int /*<<< orphan*/  fd_to_value; int /*<<< orphan*/  fd_to_ssl; } ;
struct TYPE_9__ {int recv_fd; struct TYPE_9__* next; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* on_close ) (TYPE_1__*,int,void*,int) ;TYPE_3__* private_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ ) ; 
 int FD_ISSET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HT_KEY (int) ; 
 int /*<<< orphan*/  SM_ERROR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  free (TYPE_2__**) ; 
 void* ht_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ht_size (int /*<<< orphan*/ ) ; 
 scalar_t__ ht_values (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_on_debug (TYPE_1__*,char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,void*,int) ; 

sm_status sm_remove_fd(sm_t self, int fd) {
  sm_private_t my = self->private_state;
  if (!FD_ISSET(fd, my->all_fds)) {
    return SM_ERROR;
  }
  ht_put(my->fd_to_ssl, HT_KEY(fd), NULL);
  void *value = ht_put(my->fd_to_value, HT_KEY(fd), NULL);
  bool is_server = FD_ISSET(fd, my->server_fds);
  sm_on_debug(self, "ss.remove%s_fd(%d)", (is_server ? "_server" : ""), fd);
  sm_status ret = self->on_close(self, fd, value, is_server);
#ifdef WIN32
  closesocket(fd);
#else
  close(fd);
#endif
  FD_CLR(fd, my->all_fds);
  if (is_server) {
    FD_CLR(fd, my->server_fds);
  }
  FD_CLR(fd, my->send_fds);
  FD_CLR(fd, my->recv_fds);
  FD_CLR(fd, my->tmp_send_fds);
  FD_CLR(fd, my->tmp_recv_fds);
  FD_CLR(fd, my->tmp_fail_fds);
  if (fd == my->max_fd) {
    while (my->max_fd >= 0 && !FD_ISSET(my->max_fd, my->all_fds)) {
      my->max_fd--;
    }
  }
  if (ht_size(my->fd_to_sendq)) {
    sm_sendq_t *qs = (sm_sendq_t *)ht_values(my->fd_to_sendq);
    sm_sendq_t *q;
    for (q = qs; *q; q++) {
      sm_sendq_t sendq = *q;
      while (sendq) {
        if (sendq->recv_fd == fd) {
          sendq->recv_fd = 0;
          // don't abort this blocked send, even though the "cause" has ended
        }
        sendq = sendq->next;
      }
    }
    free(qs);
  }
  return ret;
}