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
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */

__attribute__((used)) static void cl_alloc_cb(uv_handle_t* handle,
                        size_t suggested_size,
                        uv_buf_t* buf) {
  /* Do nothing, recv_cb should be called with UV_ENOBUFS. */
}