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
struct connection {int fd; int /*<<< orphan*/  flags; int /*<<< orphan*/  status; int /*<<< orphan*/  basic_type; void* extra; int /*<<< orphan*/ * type; } ;
typedef  int /*<<< orphan*/  conn_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_IPV6 ; 
 int /*<<< orphan*/  C_NOQACK ; 
 int /*<<< orphan*/  C_RAWMSG ; 
 int /*<<< orphan*/  C_SPECIAL ; 
 struct connection* Connections ; 
 int EVT_LEVEL ; 
 int EVT_RWX ; 
 int MAX_CONNECTIONS ; 
 int SM_IPV6 ; 
 int SM_LOWPRIO ; 
 int SM_NOQACK ; 
 int SM_RAWMSG ; 
 int SM_SPECIAL ; 
 int /*<<< orphan*/  accept_new_connections_gateway ; 
 scalar_t__ check_conn_functions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conn_listen ; 
 int /*<<< orphan*/  ct_listen ; 
 int /*<<< orphan*/  disable_qack (int) ; 
 int /*<<< orphan*/  epoll_insert (int,int) ; 
 int /*<<< orphan*/  epoll_sethandler (int,int,int /*<<< orphan*/ ,struct connection*) ; 
 int /*<<< orphan*/  listening_connections ; 
 int max_connection ; 
 int /*<<< orphan*/  memset (struct connection*,int /*<<< orphan*/ ,int) ; 

int init_listening_connection_ext (int fd, conn_type_t *type, void *extra, int mode, int prio) {
  if (check_conn_functions (type) < 0) {
    return -1;
  }
  if (fd >= MAX_CONNECTIONS) {
    return -1;
  }
  if (fd > max_connection) {
    max_connection = fd;
  }
  struct connection *c = Connections + fd;

  memset (c, 0, sizeof (struct connection));

  c->fd = fd;
  c->type = type;
  c->extra = extra;
  c->basic_type = ct_listen;
  c->status = conn_listen;

  if ((mode & SM_LOWPRIO)) {
    prio = 10;
  }

  epoll_sethandler (fd, prio, accept_new_connections_gateway, c);

  //  if (!(mode & SM_SPECIAL) || active_special_connections < max_special_connections) {
  epoll_insert (fd, EVT_RWX | EVT_LEVEL);
  //  }

  if ((mode & SM_SPECIAL)) {
    c->flags |= C_SPECIAL;
  }

  if ((mode & SM_NOQACK)) {
    c->flags |= C_NOQACK;
    disable_qack (c->fd);
  }

  if ((mode & SM_IPV6)) {
    c->flags |= C_IPV6;
  }

  if ((mode & SM_RAWMSG)) {
    c->flags |= C_RAWMSG;
  }

  listening_connections++;

  return 0;
}