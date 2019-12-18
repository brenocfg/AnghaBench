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
struct bitreader {int prefix_bit_offset; unsigned char const* start_ptr; unsigned char const* ptr; int m; } ;

/* Variables and functions */

void bread_init (struct bitreader *br, const unsigned char *start_ptr, int prefix_bit_offset) {
  br->prefix_bit_offset = prefix_bit_offset;
  br->start_ptr = start_ptr;
  br->ptr = start_ptr + (prefix_bit_offset >> 3);
  br->m = (((int) *br->ptr++ << 24) + (1 << 23)) << (prefix_bit_offset & 7);
}