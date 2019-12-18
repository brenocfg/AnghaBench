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
typedef  int /*<<< orphan*/  uv_handle_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  TCP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  on_connection ; 
 int /*<<< orphan*/ * server ; 
 int /*<<< orphan*/  serverType ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tcpServer ; 
 char* uv_err_name (int) ; 
 scalar_t__ uv_ip4_addr (char*,int,struct sockaddr_in*) ; 
 int uv_listen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_tcp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcp4_echo_start(int port) {
  struct sockaddr_in addr;
  int r;

  ASSERT(0 == uv_ip4_addr("0.0.0.0", port, &addr));

  server = (uv_handle_t*)&tcpServer;
  serverType = TCP;

  r = uv_tcp_init(loop, &tcpServer);
  if (r) {
    /* TODO: Error codes */
    fprintf(stderr, "Socket creation error\n");
    return 1;
  }

  r = uv_tcp_bind(&tcpServer, (const struct sockaddr*) &addr, 0);
  if (r) {
    /* TODO: Error codes */
    fprintf(stderr, "Bind error\n");
    return 1;
  }

  r = uv_listen((uv_stream_t*)&tcpServer, SOMAXCONN, on_connection);
  if (r) {
    /* TODO: Error codes */
    fprintf(stderr, "Listen error %s\n", uv_err_name(r));
    return 1;
  }

  return 0;
}