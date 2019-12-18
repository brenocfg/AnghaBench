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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct ewah_bitmap {int buffer_size; scalar_t__ bit_size; scalar_t__ buffer; } ;
typedef  int /*<<< orphan*/  eword_t ;

/* Variables and functions */

uint32_t ewah_checksum(struct ewah_bitmap *self)
{
	const uint8_t *p = (uint8_t *)self->buffer;
	uint32_t crc = (uint32_t)self->bit_size;
	size_t size = self->buffer_size * sizeof(eword_t);

	while (size--)
		crc = (crc << 5) - crc + (uint32_t)*p++;

	return crc;
}