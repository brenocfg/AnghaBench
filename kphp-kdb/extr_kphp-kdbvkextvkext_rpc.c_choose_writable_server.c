#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpc_server_collection {int num; struct rpc_server** servers; } ;
struct rpc_server {scalar_t__ status; int /*<<< orphan*/  sfd; } ;
struct TYPE_6__ {int events; int revents; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int (*) (TYPE_1__*,int,int)) ; 
 int /*<<< orphan*/  END_TIMER (int (*) (TYPE_1__*,int,int)) ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLNVAL ; 
 int POLLOUT ; 
 int POLLRDHUP ; 
 int /*<<< orphan*/  START_TIMER (int (*) (TYPE_1__*,int,int)) ; 
 int /*<<< orphan*/  errno ; 
 int get_ms_timeout (double) ; 
 int lrand48 () ; 
 int poll (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  rpc_global_seterror (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_server_failure (struct rpc_server*) ; 
 scalar_t__ rpc_status_connected ; 
 scalar_t__ rpc_work (struct rpc_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* server_fds ; 
 size_t* server_fds_tmp ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpc_server *choose_writable_server (struct rpc_server_collection *servers, double timeout) { /* {{{ */
  int i;
  int t = 0;   
  int first = 1;
  while (t || first) {
    int cc = 0;
    for (i = 0; i < servers->num; i++) if (servers->servers[i] && servers->servers[i]->status == rpc_status_connected) {
      server_fds[cc].fd = servers->servers[i]->sfd;
      server_fds[cc].events = POLLOUT | POLLERR | POLLHUP | POLLNVAL | POLLRDHUP;
      server_fds_tmp[cc] = i;
      cc ++;
    }
    if (!cc) { return 0; }
    t = get_ms_timeout (timeout);
    first = 0;

    ADD_CNT (poll);
    START_TIMER (poll);
    int r = poll (server_fds, cc, t);
    END_TIMER (poll);
    if (r < 0) {
      rpc_global_seterror (strerror (errno), errno);
      return 0;
    }
    if (r == 0) {
      return 0;
    }

    int k = 0;
    struct rpc_server *result = 0;
    for (i = 0; i < cc; i++) {
      if (server_fds[i].revents & (POLLERR | POLLHUP | POLLNVAL | POLLRDHUP)) {
        if (server_fds[i].revents & POLLRDHUP) {
          while (rpc_work (servers->servers[server_fds_tmp[i]], 0, 0) > 0); 
        }
        rpc_server_failure (servers->servers[server_fds_tmp[i]]);
      } else if (server_fds[i].revents & POLLOUT) {
        if (!(lrand48 () % (k + 1))) {
          result = servers->servers[server_fds_tmp[i]];
        }
        k ++;
      }
    }
    if (result) { return result; }
  }
  return 0;
}