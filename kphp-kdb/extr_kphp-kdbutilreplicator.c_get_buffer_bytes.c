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
struct repl_server_status {long wptr; long rptr; scalar_t__ buffer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline long get_buffer_bytes (struct repl_server_status *S) {
  long cur_buffer_bytes = S->wptr - S->rptr;
  if (cur_buffer_bytes < 0) {
    cur_buffer_bytes += S->buffer_size;
    assert (cur_buffer_bytes > 0);
  }
  return cur_buffer_bytes;
}