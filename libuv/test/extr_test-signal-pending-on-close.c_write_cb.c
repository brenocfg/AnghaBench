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
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int UV_EPIPE ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_hdl ; 
 int /*<<< orphan*/  signal_hdl ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_cb(uv_write_t* req, int status) {
  ASSERT(req != NULL);
  ASSERT(status == UV_EPIPE);
  free(buf);
  uv_close((uv_handle_t *) &pipe_hdl, close_cb);
  uv_close((uv_handle_t *) &signal_hdl, close_cb);
}