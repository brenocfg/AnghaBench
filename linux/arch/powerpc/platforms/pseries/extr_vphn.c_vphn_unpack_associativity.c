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
typedef  int u16 ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int VPHN_ASSOC_BUFSIZE ; 
 int VPHN_FIELD_MASK ; 
 int VPHN_FIELD_MSB ; 
 int VPHN_FIELD_UNUSED ; 
 int VPHN_REGISTER_COUNT ; 
 int be16_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (long const) ; 

__attribute__((used)) static int vphn_unpack_associativity(const long *packed, __be32 *unpacked)
{
	__be64 be_packed[VPHN_REGISTER_COUNT];
	int i, nr_assoc_doms = 0;
	const __be16 *field = (const __be16 *) be_packed;
	u16 last = 0;
	bool is_32bit = false;

#define VPHN_FIELD_UNUSED	(0xffff)
#define VPHN_FIELD_MSB		(0x8000)
#define VPHN_FIELD_MASK		(~VPHN_FIELD_MSB)

	/* Let's fix the values returned by plpar_hcall9() */
	for (i = 0; i < VPHN_REGISTER_COUNT; i++)
		be_packed[i] = cpu_to_be64(packed[i]);

	for (i = 1; i < VPHN_ASSOC_BUFSIZE; i++) {
		u16 new = be16_to_cpup(field++);

		if (is_32bit) {
			/*
			 * Let's concatenate the 16 bits of this field to the
			 * 15 lower bits of the previous field
			 */
			unpacked[++nr_assoc_doms] =
				cpu_to_be32(last << 16 | new);
			is_32bit = false;
		} else if (new == VPHN_FIELD_UNUSED)
			/* This is the list terminator */
			break;
		else if (new & VPHN_FIELD_MSB) {
			/* Data is in the lower 15 bits of this field */
			unpacked[++nr_assoc_doms] =
				cpu_to_be32(new & VPHN_FIELD_MASK);
		} else {
			/*
			 * Data is in the lower 15 bits of this field
			 * concatenated with the next 16 bit field
			 */
			last = new;
			is_32bit = true;
		}
	}

	/* The first cell contains the length of the property */
	unpacked[0] = cpu_to_be32(nr_assoc_doms);

	return nr_assoc_doms;
}