#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int count; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* reseed ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ isc_lfsr_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_LFSR (TYPE_1__*) ; 
 unsigned char lfsr_generate (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
isc_lfsr_generate(isc_lfsr_t *lfsr, void *data, unsigned int count)
{
	unsigned char *p;
	unsigned int bit;
	unsigned int byte;

	REQUIRE(VALID_LFSR(lfsr));
	REQUIRE(data != NULL);
	REQUIRE(count > 0);

	p = data;
	byte = count;

	while (byte--) {
		*p = 0;
		for (bit = 0; bit < 7; bit++) {
			*p |= lfsr_generate(lfsr);
			*p <<= 1;
		}
		*p |= lfsr_generate(lfsr);
		p++;
	}

	if (lfsr->count != 0 && lfsr->reseed != NULL) {
		if (lfsr->count <= count * 8)
			lfsr->reseed(lfsr, lfsr->arg);
		else
			lfsr->count -= (count * 8);
	}
}