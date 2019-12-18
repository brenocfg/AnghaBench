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
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_3__ {char* base; int len; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  int /*<<< orphan*/  base ;

/* Variables and functions */

__attribute__((used)) static void alloc_cb(uv_handle_t* handle, size_t size, uv_buf_t* buf) {
  static char base[1024];

  buf->base = base;
  buf->len = sizeof(base);
}