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
typedef  int uint32_t ;
struct TYPE_3__ {int bitoffs; int bitlen; } ;
typedef  TYPE_1__ ib_field_t ;

/* Variables and functions */

__attribute__((used)) static void _set_field(void *buf, int base_offs, const ib_field_t * f,
		       uint32_t val)
{
	int prebits = (8 - (f->bitoffs & 7)) & 7;
	int postbits = (f->bitoffs + f->bitlen) & 7;
	int bytelen = f->bitlen / 8;
	unsigned idx = base_offs + f->bitoffs / 8;
	char *p = (char *)buf;

	if (!bytelen && (f->bitoffs & 7) + f->bitlen < 8) {
		p[3 ^ idx] &= ~((((1 << f->bitlen) - 1)) << (f->bitoffs & 7));
		p[3 ^ idx] |=
		    (val & ((1 << f->bitlen) - 1)) << (f->bitoffs & 7);
		return;
	}

	if (prebits) {		/* val lsb in byte msb */
		p[3 ^ idx] &= (1 << (8 - prebits)) - 1;
		p[3 ^ idx++] |= (val & ((1 << prebits) - 1)) << (8 - prebits);
		val >>= prebits;
	}

	/* BIG endian byte order */
	for (; bytelen--; val >>= 8)
		p[3 ^ idx++] = val & 0xff;

	if (postbits) {		/* val msb in byte lsb */
		p[3 ^ idx] &= ~((1 << postbits) - 1);
		p[3 ^ idx] |= val;
	}
}