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
struct TYPE_3__ {int bit_offset; int /*<<< orphan*/  len; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ istream_t ;
typedef  int i64 ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 

__attribute__((used)) static inline void IO_rewind_bits(istream_t *const in, int num_bits) {
    if (num_bits < 0) {
        ERROR("Attempting to rewind stream by a negative number of bits");
    }

    // move the offset back by `num_bits` bits
    const int new_offset = in->bit_offset - num_bits;
    // determine the number of whole bytes we have to rewind, rounding up to an
    // integer number (e.g. if `new_offset == -5`, `bytes == 1`)
    const i64 bytes = -(new_offset - 7) / 8;

    in->ptr -= bytes;
    in->len += bytes;
    // make sure the resulting `bit_offset` is positive, as mod in C does not
    // convert numbers from negative to positive (e.g. -22 % 8 == -6)
    in->bit_offset = ((new_offset % 8) + 8) % 8;
}