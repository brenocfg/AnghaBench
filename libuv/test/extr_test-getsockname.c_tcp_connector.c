#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ connect_port ; 
 int /*<<< orphan*/  connect_req ; 
 int /*<<< orphan*/  loop ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_connect ; 
 int /*<<< orphan*/  server_port ; 
 TYPE_1__ tcp ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_tcp_connect (int /*<<< orphan*/ *,TYPE_1__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_getsockname (TYPE_1__*,struct sockaddr*,int*) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void tcp_connector(void) {
  struct sockaddr_in server_addr;
  struct sockaddr sockname;
  int r, namelen;

  ASSERT(0 == uv_ip4_addr("127.0.0.1", server_port, &server_addr));

  r = uv_tcp_init(loop, &tcp);
  tcp.data = &connect_req;
  ASSERT(!r);

  r = uv_tcp_connect(&connect_req,
                     &tcp,
                     (const struct sockaddr*) &server_addr,
                     on_connect);
  ASSERT(!r);

  /* Fetch the actual port used by the connecting socket. */
  namelen = sizeof sockname;
  r = uv_tcp_getsockname(&tcp, &sockname, &namelen);
  ASSERT(!r);
  ASSERT(sockname.sa_family == AF_INET);
  connect_port = ntohs(((struct sockaddr_in*) &sockname)->sin_port);
  ASSERT(connect_port > 0);
}