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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int bitoffs; int bitlen; } ;
typedef  TYPE_1__ ib_field_t ;

/* Variables and functions */
 int BE_TO_BITSOFFS (int,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _get_array(void *buf, int base_offs, const ib_field_t * f,
		       void *val)
{
	int bitoffs = f->bitoffs;

	if (f->bitlen < 32)
		bitoffs = BE_TO_BITSOFFS(bitoffs, f->bitlen);

	memcpy(val, (uint8_t *) buf + base_offs + bitoffs / 8, f->bitlen / 8);
}