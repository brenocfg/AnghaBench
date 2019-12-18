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
struct msg_buffers_chunk {unsigned int bs_shift; unsigned int bs_inverse; int buffer_size; scalar_t__ first_buffer; scalar_t__ tot_buffers; } ;
struct msg_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

inline int get_buffer_no (struct msg_buffers_chunk *C, struct msg_buffer *X) {
  unsigned x = ((char *) X - (char *) C->first_buffer);
  x >>= C->bs_shift;
  x *= C->bs_inverse;
  assert (x <= (unsigned) C->tot_buffers && (char *) X == (char *) C->first_buffer + (C->buffer_size + 16) * x);
  return x;
}