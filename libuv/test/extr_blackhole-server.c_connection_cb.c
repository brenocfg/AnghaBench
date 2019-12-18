#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;
struct TYPE_9__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ conn_rec ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  alloc_cb ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  read_cb ; 
 int /*<<< orphan*/  tcp_server ; 
 int uv_accept (TYPE_1__*,TYPE_1__*) ; 
 int uv_read_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void connection_cb(uv_stream_t* stream, int status) {
  conn_rec* conn;
  int r;

  ASSERT(status == 0);
  ASSERT(stream == (uv_stream_t*)&tcp_server);

  conn = malloc(sizeof *conn);
  ASSERT(conn != NULL);

  r = uv_tcp_init(stream->loop, &conn->handle);
  ASSERT(r == 0);

  r = uv_accept(stream, (uv_stream_t*)&conn->handle);
  ASSERT(r == 0);

  r = uv_read_start((uv_stream_t*)&conn->handle, alloc_cb, read_cb);
  ASSERT(r == 0);
}