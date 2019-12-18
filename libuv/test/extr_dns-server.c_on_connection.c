#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_3__ {scalar_t__ prevbuf_rem; scalar_t__ prevbuf_pos; scalar_t__ prevbuf_ptr; } ;
struct TYPE_4__ {TYPE_1__ state; } ;
typedef  TYPE_2__ dnshandle ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  after_read ; 
 int /*<<< orphan*/  buf_alloc ; 
 int /*<<< orphan*/  loop ; 
 scalar_t__ malloc (int) ; 
 int uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_connection(uv_stream_t* server, int status) {
  dnshandle* handle;
  int r;

  ASSERT(status == 0);

  handle = (dnshandle*) malloc(sizeof *handle);
  ASSERT(handle != NULL);

  /* initialize read buffer state */
  handle->state.prevbuf_ptr = 0;
  handle->state.prevbuf_pos = 0;
  handle->state.prevbuf_rem = 0;

  r = uv_tcp_init(loop, (uv_tcp_t*)handle);
  ASSERT(r == 0);

  r = uv_accept(server, (uv_stream_t*)handle);
  ASSERT(r == 0);

  r = uv_read_start((uv_stream_t*)handle, buf_alloc, after_read);
  ASSERT(r == 0);
}