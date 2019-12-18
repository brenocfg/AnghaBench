#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_3__ {scalar_t__ handle; } ;
typedef  TYPE_1__ uv_connect_t ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  check_sockname (struct sockaddr*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getpeernamecount ; 
 int /*<<< orphan*/  getsocknamecount ; 
 int /*<<< orphan*/  server_port ; 
 int /*<<< orphan*/  tcp ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_tcp_getpeername (int /*<<< orphan*/ *,struct sockaddr*,int*) ; 
 int uv_tcp_getsockname (int /*<<< orphan*/ *,struct sockaddr*,int*) ; 

__attribute__((used)) static void on_connect(uv_connect_t* req, int status) {
  struct sockaddr sockname, peername;
  int r, namelen;

  ASSERT(status == 0);

  namelen = sizeof sockname;
  r = uv_tcp_getsockname((uv_tcp_t*) req->handle, &sockname, &namelen);
  ASSERT(r == 0);
  check_sockname(&sockname, "127.0.0.1", 0, "connected socket");
  getsocknamecount++;

  namelen = sizeof peername;
  r = uv_tcp_getpeername((uv_tcp_t*) req->handle, &peername, &namelen);
  ASSERT(r == 0);
  check_sockname(&peername, "127.0.0.1", server_port, "connected socket peer");
  getpeernamecount++;

  uv_close((uv_handle_t*)&tcp, NULL);
}