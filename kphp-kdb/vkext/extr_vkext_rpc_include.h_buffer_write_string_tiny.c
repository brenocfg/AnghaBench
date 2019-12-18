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
struct rpc_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buffer_write_char (struct rpc_buffer*,int) ; 
 int /*<<< orphan*/  buffer_write_data (struct rpc_buffer*,char const*,int) ; 
 int /*<<< orphan*/  buffer_write_pad (struct rpc_buffer*) ; 

__attribute__((used)) static inline void buffer_write_string_tiny (struct rpc_buffer *buf, int len, const char *s) {
  assert (len <= 253);
  buffer_write_char (buf, len);
  buffer_write_data (buf, s, len);
  buffer_write_pad (buf);
}