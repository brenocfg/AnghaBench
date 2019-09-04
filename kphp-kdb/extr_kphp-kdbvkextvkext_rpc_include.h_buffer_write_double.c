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
typedef  int /*<<< orphan*/  x ;
struct rpc_buffer {scalar_t__ wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_check_len_wptr (struct rpc_buffer*,int) ; 

__attribute__((used)) static inline void buffer_write_double (struct rpc_buffer *buf, double x) {
  buffer_check_len_wptr (buf, sizeof (x));
  *(double *)(buf->wptr) = x;
  buf->wptr += sizeof (x);
}