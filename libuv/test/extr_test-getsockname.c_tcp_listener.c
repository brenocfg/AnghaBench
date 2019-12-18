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
typedef  int /*<<< orphan*/  uv_stream_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int UV_ENOTCONN ; 
 int /*<<< orphan*/  check_sockname (struct sockaddr*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getpeernamecount ; 
 int /*<<< orphan*/  getsocknamecount ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int,int) ; 
 int /*<<< orphan*/  on_connection ; 
 int /*<<< orphan*/  server_port ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tcpServer ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_listen (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int uv_tcp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_getpeername (int /*<<< orphan*/ *,struct sockaddr*,int*) ; 
 int uv_tcp_getsockname (int /*<<< orphan*/ *,struct sockaddr*,int*) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcp_listener(void) {
  struct sockaddr_in addr;
  struct sockaddr sockname, peername;
  int namelen;
  int r;

  ASSERT(0 == uv_ip4_addr("0.0.0.0", server_port, &addr));

  r = uv_tcp_init(loop, &tcpServer);
  if (r) {
    fprintf(stderr, "Socket creation error\n");
    return 1;
  }

  r = uv_tcp_bind(&tcpServer, (const struct sockaddr*) &addr, 0);
  if (r) {
    fprintf(stderr, "Bind error\n");
    return 1;
  }

  r = uv_listen((uv_stream_t*)&tcpServer, 128, on_connection);
  if (r) {
    fprintf(stderr, "Listen error\n");
    return 1;
  }

  memset(&sockname, -1, sizeof sockname);
  namelen = sizeof sockname;
  r = uv_tcp_getsockname(&tcpServer, &sockname, &namelen);
  ASSERT(r == 0);
  check_sockname(&sockname, "0.0.0.0", server_port, "server socket");
  getsocknamecount++;

  namelen = sizeof sockname;
  r = uv_tcp_getpeername(&tcpServer, &peername, &namelen);
  ASSERT(r == UV_ENOTCONN);
  getpeernamecount++;

  return 0;
}