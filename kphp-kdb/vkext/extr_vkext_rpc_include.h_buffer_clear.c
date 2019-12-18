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
struct rpc_buffer {int /*<<< orphan*/  sptr; int /*<<< orphan*/  wptr; int /*<<< orphan*/  rptr; } ;

/* Variables and functions */

__attribute__((used)) static inline void buffer_clear (struct rpc_buffer *buf) {
  buf->rptr = buf->wptr = buf->sptr;
}