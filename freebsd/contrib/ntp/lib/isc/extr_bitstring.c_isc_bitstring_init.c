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
typedef  int /*<<< orphan*/  isc_boolean_t ;
struct TYPE_3__ {unsigned char* data; unsigned int length; unsigned int size; int /*<<< orphan*/  lsb0; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ isc_bitstring_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITSTRING_MAGIC ; 
 int /*<<< orphan*/  REQUIRE (int) ; 

void
isc_bitstring_init(isc_bitstring_t *bitstring, unsigned char *data,
		   unsigned int length, unsigned int size, isc_boolean_t lsb0)
{
	/*
	 * Make 'bitstring' refer to the bitstring of 'size' bits starting
	 * at 'data'.  'length' bits of the bitstring are valid.  If 'lsb0'
	 * is set then, bit 0 refers to the least significant bit of the
	 * bitstring.  Otherwise bit 0 is the most significant bit.
	 */

	REQUIRE(bitstring != NULL);
	REQUIRE(data != NULL);
	REQUIRE(length <= size);

	bitstring->magic = BITSTRING_MAGIC;
	bitstring->data = data;
	bitstring->length = length;
	bitstring->size = size;
	bitstring->lsb0 = lsb0;
}