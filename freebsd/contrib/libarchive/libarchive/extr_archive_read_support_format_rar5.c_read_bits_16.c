#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {size_t in_addr; int bit_addr; } ;
struct rar5 {TYPE_1__ bits; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 

__attribute__((used)) static int read_bits_16(struct rar5* rar, const uint8_t* p, uint16_t* value) {
	int bits = (int) ((uint32_t) p[rar->bits.in_addr]) << 16;
	bits |= (int) p[rar->bits.in_addr + 1] << 8;
	bits |= (int) p[rar->bits.in_addr + 2];
	bits >>= (8 - rar->bits.bit_addr);
	*value = bits & 0xffff;
	return ARCHIVE_OK;
}