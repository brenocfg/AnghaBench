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
typedef  int /*<<< orphan*/  uv_pipe_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ TCP ; 
 int /*<<< orphan*/  buf_alloc ; 
 int /*<<< orphan*/  loop ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  max_read_sockets ; 
 int /*<<< orphan*/  read_cb ; 
 int /*<<< orphan*/  read_sockets ; 
 int /*<<< orphan*/ * server ; 
 scalar_t__ type ; 
 int uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void connection_cb(uv_stream_t* s, int status) {
  uv_stream_t* stream;
  int r;

  ASSERT(server == s);
  ASSERT(status == 0);

  if (type == TCP) {
    stream = (uv_stream_t*)malloc(sizeof(uv_tcp_t));
    r = uv_tcp_init(loop, (uv_tcp_t*)stream);
    ASSERT(r == 0);
  } else {
    stream = (uv_stream_t*)malloc(sizeof(uv_pipe_t));
    r = uv_pipe_init(loop, (uv_pipe_t*)stream, 0);
    ASSERT(r == 0);
  }

  r = uv_accept(s, stream);
  ASSERT(r == 0);

  r = uv_read_start(stream, buf_alloc, read_cb);
  ASSERT(r == 0);

  read_sockets++;
  max_read_sockets++;
}