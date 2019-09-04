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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  alloc ; 
 int /*<<< orphan*/  check_sockname (struct sockaddr*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getsocknamecount ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int,int) ; 
 int /*<<< orphan*/  server_port ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  udpServer ; 
 int /*<<< orphan*/  udp_recv ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_udp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_udp_getsockname (int /*<<< orphan*/ *,struct sockaddr*,int*) ; 
 int uv_udp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_udp_recv_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udp_listener(void) {
  struct sockaddr_in addr;
  struct sockaddr sockname;
  int namelen;
  int r;

  ASSERT(0 == uv_ip4_addr("0.0.0.0", server_port, &addr));

  r = uv_udp_init(loop, &udpServer);
  if (r) {
    fprintf(stderr, "Socket creation error\n");
    return 1;
  }

  r = uv_udp_bind(&udpServer, (const struct sockaddr*) &addr, 0);
  if (r) {
    fprintf(stderr, "Bind error\n");
    return 1;
  }

  memset(&sockname, -1, sizeof sockname);
  namelen = sizeof sockname;
  r = uv_udp_getsockname(&udpServer, &sockname, &namelen);
  ASSERT(r == 0);
  check_sockname(&sockname, "0.0.0.0", server_port, "udp listener socket");
  getsocknamecount++;

  r = uv_udp_recv_start(&udpServer, alloc, udp_recv);
  ASSERT(r == 0);

  return 0;
}