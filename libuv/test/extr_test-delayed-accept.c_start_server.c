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
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  connection_cb ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_listen (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int uv_tcp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_server(void) {
  struct sockaddr_in addr;
  uv_tcp_t* server = (uv_tcp_t*)malloc(sizeof *server);
  int r;

  ASSERT(0 == uv_ip4_addr("0.0.0.0", TEST_PORT, &addr));
  ASSERT(server != NULL);

  r = uv_tcp_init(uv_default_loop(), server);
  ASSERT(r == 0);
  r = uv_tcp_bind(server, (const struct sockaddr*) &addr, 0);
  ASSERT(r == 0);

  r = uv_listen((uv_stream_t*)server, 128, connection_cb);
  ASSERT(r == 0);
}