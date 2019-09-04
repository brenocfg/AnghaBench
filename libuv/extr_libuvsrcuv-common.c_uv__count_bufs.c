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
struct TYPE_3__ {scalar_t__ len; } ;
typedef  TYPE_1__ uv_buf_t ;

/* Variables and functions */

size_t uv__count_bufs(const uv_buf_t bufs[], unsigned int nbufs) {
  unsigned int i;
  size_t bytes;

  bytes = 0;
  for (i = 0; i < nbufs; i++)
    bytes += (size_t) bufs[i].len;

  return bytes;
}