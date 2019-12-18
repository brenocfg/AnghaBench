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
struct TYPE_3__ {size_t len; size_t base; } ;
typedef  TYPE_1__ uv_buf_t ;

/* Variables and functions */

__attribute__((used)) static size_t uv__fs_buf_offset(uv_buf_t* bufs, size_t size) {
  size_t offset;
  /* Figure out which bufs are done */
  for (offset = 0; size > 0 && bufs[offset].len <= size; ++offset)
    size -= bufs[offset].len;

  /* Fix a partial read/write */
  if (size > 0) {
    bufs[offset].base += size;
    bufs[offset].len -= size;
  }
  return offset;
}