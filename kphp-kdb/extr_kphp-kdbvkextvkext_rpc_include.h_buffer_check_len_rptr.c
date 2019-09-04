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
struct rpc_buffer {scalar_t__ rptr; scalar_t__ wptr; } ;

/* Variables and functions */

__attribute__((used)) static inline int buffer_check_len_rptr (struct rpc_buffer *buf, int x) {
  return (buf->rptr + x <= buf->wptr);
}