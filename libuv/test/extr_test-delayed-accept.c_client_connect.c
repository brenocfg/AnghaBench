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
typedef  int /*<<< orphan*/  uv_connect_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  connect_cb ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_tcp_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void client_connect(void) {
  struct sockaddr_in addr;
  uv_tcp_t* client = (uv_tcp_t*)malloc(sizeof *client);
  uv_connect_t* connect_req = malloc(sizeof *connect_req);
  int r;

  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &addr));
  ASSERT(client != NULL);
  ASSERT(connect_req != NULL);

  r = uv_tcp_init(uv_default_loop(), client);
  ASSERT(r == 0);

  r = uv_tcp_connect(connect_req,
                     client,
                     (const struct sockaddr*) &addr,
                     connect_cb);
  ASSERT(r == 0);
}