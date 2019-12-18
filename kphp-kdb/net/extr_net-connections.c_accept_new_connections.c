#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ magic; } ;
struct TYPE_13__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_14__ {scalar_t__ sin6_family; TYPE_4__ sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_12__ {scalar_t__ sin_family; int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  wakeup; } ;
struct TYPE_17__ {scalar_t__ state; } ;
union sockaddr_in46 {scalar_t__ basic_type; int fd; int flags; int listening; int window_clamp; TYPE_7__ out_p; TYPE_7__ in_u; TYPE_7__ out; TYPE_7__ in; scalar_t__ generation; scalar_t__ listening_generation; TYPE_6__* type; void* our_port; void* remote_port; struct conn_query* last_query; struct conn_query* first_query; TYPE_5__ a6; int /*<<< orphan*/  remote_ipv6; int /*<<< orphan*/  our_ipv6; void* remote_ip; void* our_ip; TYPE_3__ a4; int /*<<< orphan*/  status; int /*<<< orphan*/  extra; TYPE_1__ timer; int /*<<< orphan*/  out_buff; TYPE_9__ Out; int /*<<< orphan*/  in_buff; TYPE_9__ In; int /*<<< orphan*/ * ev; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct connection {scalar_t__ basic_type; int fd; int flags; int listening; int window_clamp; TYPE_7__ out_p; TYPE_7__ in_u; TYPE_7__ out; TYPE_7__ in; scalar_t__ generation; scalar_t__ listening_generation; TYPE_6__* type; void* our_port; void* remote_port; struct conn_query* last_query; struct conn_query* first_query; TYPE_5__ a6; int /*<<< orphan*/  remote_ipv6; int /*<<< orphan*/  our_ipv6; void* remote_ip; void* our_ip; TYPE_3__ a4; int /*<<< orphan*/  status; int /*<<< orphan*/  extra; TYPE_1__ timer; int /*<<< orphan*/  out_buff; TYPE_9__ Out; int /*<<< orphan*/  in_buff; TYPE_9__ In; int /*<<< orphan*/ * ev; } ;
struct conn_query {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  self ;
typedef  int /*<<< orphan*/  peer ;
typedef  int /*<<< orphan*/  flags ;
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_15__ {int flags; scalar_t__ (* init_accepted ) (union sockaddr_in46*) ;int /*<<< orphan*/  title; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  BUFF_SIZE ; 
 int C_IPV6 ; 
 int C_NOQACK ; 
 int C_RAWMSG ; 
 int C_SPECIAL ; 
 int C_WANTRD ; 
 int C_WANTWR ; 
 union sockaddr_in46* Connections ; 
 scalar_t__ EAGAIN ; 
 int EVA_CONTINUE ; 
 int EVA_REMOVE ; 
 int EVT_READ ; 
 int EVT_SPEC ; 
 int EVT_WRITE ; 
 int /*<<< orphan*/ * Events ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int MAX_CONNECTIONS ; 
 int MAX_EVENTS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  TCP_WINDOW_CLAMP ; 
 int accept (int,struct sockaddr*,unsigned int*) ; 
 int /*<<< orphan*/  active_connections ; 
 scalar_t__ active_special_connections ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  conn_expect_query ; 
 scalar_t__ conn_generation ; 
 int /*<<< orphan*/  conn_timer_wakeup_gateway ; 
 int /*<<< orphan*/  conv_addr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  conv_addr6 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ct_inbound ; 
 scalar_t__ ct_listen ; 
 scalar_t__ ct_none ; 
 int /*<<< orphan*/  epoll_insert (int,int) ; 
 int /*<<< orphan*/  epoll_sethandler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union sockaddr_in46*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  extract_4in6 (int /*<<< orphan*/ ) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  getsockname (int,struct sockaddr*,unsigned int*) ; 
 int /*<<< orphan*/  getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  inbound_connections_accepted ; 
 int /*<<< orphan*/  init_builtin_buffer (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int is_4in6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__,...) ; 
 int max_connection ; 
 scalar_t__ max_special_connections ; 
 int maxconn ; 
 int /*<<< orphan*/  maximize_rcvbuf (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maximize_sndbuf (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (union sockaddr_in46*,int /*<<< orphan*/ ,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwm_free (TYPE_7__*) ; 
 int /*<<< orphan*/  rwm_init (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_read_write_gateway ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  show_our_ip (union sockaddr_in46*) ; 
 int /*<<< orphan*/  show_remote_ip (union sockaddr_in46*) ; 
 scalar_t__ stub1 (union sockaddr_in46*) ; 
 scalar_t__ tcp_maximize_buffers ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int,...) ; 

int accept_new_connections (struct connection *cc) {
  char buf[64], buf2[64];
  union sockaddr_in46 peer, self;
  unsigned peer_addrlen, self_addrlen;
  int cfd, acc = 0, flags;
  struct connection *c;
  event_t *ev;

  assert (cc->basic_type == ct_listen);
  do {
    peer_addrlen = sizeof (peer);
    self_addrlen = sizeof (self);
    memset (&peer, 0, sizeof (peer));
    memset (&self, 0, sizeof (self));
    cfd = accept (cc->fd, (struct sockaddr *) &peer, &peer_addrlen);
    if (cfd < 0) {
      if (!acc) {
	vkprintf (errno == EAGAIN ? 1 : 0, "accept(%d) unexpectedly returns %d: %m\n", cc->fd, cfd);
      }
      break;
    }
    acc++;
    inbound_connections_accepted++;
    getsockname (cfd, (struct sockaddr *) &self, &self_addrlen);
    assert (cfd < MAX_EVENTS);
    ev = Events + cfd;
    assert (peer_addrlen == self_addrlen);
    if (cc->flags & C_IPV6) {
      assert (peer_addrlen == sizeof (struct sockaddr_in6));
      assert (peer.a6.sin6_family == AF_INET6);
      assert (self.a6.sin6_family == AF_INET6);
    } else {
      assert (peer_addrlen == sizeof (struct sockaddr_in));
      assert (peer.a4.sin_family == AF_INET);
      assert (self.a4.sin_family == AF_INET);
    }
    // memcpy (&ev->peer, &peer, sizeof(peer));
    if (peer.a4.sin_family == AF_INET) {
      vkprintf (1, "accepted incoming connection of type %s at %s:%d -> %s:%d, fd=%d\n", cc->type->title, conv_addr (peer.a4.sin_addr.s_addr, buf), ntohs (peer.a4.sin_port), conv_addr (self.a4.sin_addr.s_addr, buf2), ntohs (self.a4.sin_port), cfd);
    } else {
      vkprintf (1, "accepted incoming ipv6 connection of type %s at [%s]:%d -> [%s]:%d, fd=%d\n", cc->type->title, conv_addr6 (peer.a6.sin6_addr.s6_addr, buf), ntohs (peer.a6.sin6_port), conv_addr6 (self.a6.sin6_addr.s6_addr, buf2), ntohs (self.a6.sin6_port), cfd);
    }
    if ((flags = fcntl (cfd, F_GETFL, 0) < 0) || fcntl (cfd, F_SETFL, flags | O_NONBLOCK) < 0) {
      kprintf ("cannot set O_NONBLOCK on accepted socket %d: %m\n", cfd);
      close (cfd);
      continue;
    }
    if (cfd >= MAX_CONNECTIONS || (cfd >= maxconn && maxconn)) {
      close (cfd);
      continue;
    }
    if (cfd > max_connection) {
      max_connection = cfd;
    }
    flags = 1;
    setsockopt (cfd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof (flags));
    if (tcp_maximize_buffers) {
      maximize_sndbuf (cfd, 0);
      maximize_rcvbuf (cfd, 0);
    }

    c = Connections + cfd;
    memset (c, 0, sizeof (struct connection));
    c->fd = cfd;
    c->ev = ev;
    c->generation = ++conn_generation;
    c->flags = C_WANTRD;
    if ((cc->flags & C_RAWMSG) || (cc->type->flags & C_RAWMSG)) {
      c->flags |= C_RAWMSG;
      c->In.state = c->Out.state = 0;
      rwm_init (&c->in, 0); 
      rwm_init (&c->out, 0); 
      rwm_init (&c->in_u, 0); 
      rwm_init (&c->out_p, 0); 
    } else {
      c->in.magic = c->out.magic = 0;
      init_builtin_buffer (&c->In, c->in_buff, BUFF_SIZE);
      init_builtin_buffer (&c->Out, c->out_buff, BUFF_SIZE);
    }
    c->timer.wakeup = conn_timer_wakeup_gateway;
    c->type = cc->type;
    c->extra = cc->extra;
    c->basic_type = ct_inbound;
    c->status = conn_expect_query;
    if (peer.a4.sin_family == AF_INET) {
      c->our_ip = ntohl (self.a4.sin_addr.s_addr);
      c->our_port = ntohs (self.a4.sin_port);
      c->remote_ip = ntohl (peer.a4.sin_addr.s_addr);
      c->remote_port = ntohs (peer.a4.sin_port);
    } else if (is_4in6 (peer.a6.sin6_addr.s6_addr)) {
      assert (is_4in6 (self.a6.sin6_addr.s6_addr));
      c->our_ip = ntohl (extract_4in6 (self.a6.sin6_addr.s6_addr));
      c->our_port = ntohs (self.a6.sin6_port);
      c->remote_ip = ntohl (extract_4in6 (peer.a6.sin6_addr.s6_addr));
      c->remote_port = ntohs (peer.a6.sin6_port);
    } else {
      c->our_port = ntohs (self.a6.sin6_port);
      c->remote_port = ntohs (peer.a6.sin6_port);
      memcpy (c->our_ipv6, self.a6.sin6_addr.s6_addr, 16);
      memcpy (c->remote_ipv6, peer.a6.sin6_addr.s6_addr, 16);
      c->flags |= C_IPV6;
    }
    c->first_query = c->last_query = (struct conn_query *) c;
    vkprintf (2, "accepted incoming connection of type %s at %s:%d -> %s:%d, fd=%d\n", c->type->title, show_remote_ip (c), c->remote_port, show_our_ip (c), c->our_port, cfd);
    if (c->type->init_accepted (c) >= 0) {
      epoll_sethandler (cfd, 0, server_read_write_gateway, c);
      epoll_insert (cfd, (c->flags & C_WANTRD ? EVT_READ : 0) | (c->flags & C_WANTWR ? EVT_WRITE : 0) | EVT_SPEC);
      active_connections++;
      c->listening = cc->fd;
      c->listening_generation = cc->generation;
      if (cc->flags & C_SPECIAL) {
	c->flags |= C_SPECIAL;
	if (active_special_connections >= max_special_connections) {
	  kprintf ("ERROR: forced to accept connection when special connections limit was reached (%d of %d)\n", active_special_connections, max_special_connections);
	}
	if (++active_special_connections >= max_special_connections) {
	  return EVA_REMOVE;
	}
      }
      if ((cc->flags & C_NOQACK)) {
	c->flags |= C_NOQACK;
	// disable_qack (c->fd);
      }
      c->window_clamp = cc->window_clamp;
      if (c->window_clamp) {
	if (setsockopt (cfd, IPPROTO_TCP, TCP_WINDOW_CLAMP, &c->window_clamp, 4) < 0) {
	  vkprintf (0, "error while setting window size for socket %d to %d: %m\n", cfd, c->window_clamp);
	} else {
	  int t1 = -1, t2 = -1;
	  socklen_t s1 = 4, s2 = 4;
	  getsockopt (cfd, IPPROTO_TCP, TCP_WINDOW_CLAMP, &t1, &s1);
	  getsockopt (cfd, SOL_SOCKET, SO_RCVBUF, &t2, &s2);
	  vkprintf (2, "window clamp for socket %d is %d, receive buffer is %d\n", cfd, t1, t2);
	}
      }
    } else {
      if (c->flags & C_RAWMSG) {
	rwm_free (&c->in);
	rwm_free (&c->out);
	rwm_free (&c->in_u);
	rwm_free (&c->out_p);
      }
      c->basic_type = ct_none;
      close (cfd);
    }
  } while (1);
  return EVA_CONTINUE;
}