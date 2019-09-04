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
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  after_read ; 
 int /*<<< orphan*/  alloc ; 
 int /*<<< orphan*/  check_sockname (struct sockaddr*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  connect_port ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  getpeernamecount ; 
 int /*<<< orphan*/  getsocknamecount ; 
 int /*<<< orphan*/  loop ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  server_port ; 
 int /*<<< orphan*/  stderr ; 
 int uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* uv_err_name (int) ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_tcp_getpeername (TYPE_1__*,struct sockaddr*,int*) ; 
 int uv_tcp_getsockname (TYPE_1__*,struct sockaddr*,int*) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void on_connection(uv_stream_t* server, int status) {
  struct sockaddr sockname, peername;
  int namelen;
  uv_tcp_t* handle;
  int r;

  if (status != 0) {
    fprintf(stderr, "Connect error %s\n", uv_err_name(status));
  }
  ASSERT(status == 0);

  handle = malloc(sizeof(*handle));
  ASSERT(handle != NULL);

  r = uv_tcp_init(loop, handle);
  ASSERT(r == 0);

  /* associate server with stream */
  handle->data = server;

  r = uv_accept(server, (uv_stream_t*)handle);
  ASSERT(r == 0);

  namelen = sizeof sockname;
  r = uv_tcp_getsockname(handle, &sockname, &namelen);
  ASSERT(r == 0);
  check_sockname(&sockname, "127.0.0.1", server_port, "accepted socket");
  getsocknamecount++;

  namelen = sizeof peername;
  r = uv_tcp_getpeername(handle, &peername, &namelen);
  ASSERT(r == 0);
  check_sockname(&peername, "127.0.0.1", connect_port, "accepted socket peer");
  getpeernamecount++;

  r = uv_read_start((uv_stream_t*)handle, alloc, after_read);
  ASSERT(r == 0);
}