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
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_EOF ; 
 int /*<<< orphan*/  after_write ; 
 int /*<<< orphan*/  in ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_read_cb_called ; 
 int /*<<< orphan*/  output ; 
 int output_used ; 
 int /*<<< orphan*/  uv_buf_init (int /*<<< orphan*/ ,int) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* rdbuf) {
  uv_write_t* req;
  uv_buf_t wrbuf;
  int r;

  ASSERT(nread > 0 || nread == UV_EOF);

  if (nread > 0) {
    output_used += nread;
    if (output_used == 12) {
      ASSERT(memcmp("hello world\n", output, 12) == 0);
      wrbuf = uv_buf_init(output, output_used);
      req = malloc(sizeof(*req));
      r = uv_write(req, (uv_stream_t*)&in, &wrbuf, 1, after_write);
      ASSERT(r == 0);
    }
  }

  on_read_cb_called++;
}