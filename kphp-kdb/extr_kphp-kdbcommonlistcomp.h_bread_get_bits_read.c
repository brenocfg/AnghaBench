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
struct bitreader {int ptr; int start_ptr; int prefix_bit_offset; int /*<<< orphan*/  m; } ;

/* Variables and functions */
 int ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int bread_get_bits_read (const struct bitreader *br) {
  return ((br->ptr - br->start_ptr) << 3) + (ffs (br->m) - 32) - br->prefix_bit_offset;
}