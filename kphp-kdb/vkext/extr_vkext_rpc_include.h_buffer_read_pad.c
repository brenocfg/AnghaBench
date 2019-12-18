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
struct rpc_buffer {int sptr; int rptr; } ;

/* Variables and functions */

__attribute__((used)) static inline int buffer_read_pad (struct rpc_buffer *buf) {
  int pad_bytes = (buf->sptr - buf->rptr) & 3;
  buf->rptr += pad_bytes;
  return 1;
}