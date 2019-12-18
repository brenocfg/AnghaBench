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
struct exception_table_entry {int fixup; unsigned long insn; } ;

/* Variables and functions */

const struct exception_table_entry *
search_extable(const struct exception_table_entry *base,
	       const size_t num,
	       unsigned long value)
{
	int i;

	/* Single insn entries are encoded as:
	 *	word 1:	insn address
	 *	word 2:	fixup code address
	 *
	 * Range entries are encoded as:
	 *	word 1: first insn address
	 *	word 2: 0
	 *	word 3: last insn address + 4 bytes
	 *	word 4: fixup code address
	 *
	 * Deleted entries are encoded as:
	 *	word 1: unused
	 *	word 2: -1
	 *
	 * See asm/uaccess.h for more details.
	 */

	/* 1. Try to find an exact match. */
	for (i = 0; i < num; i++) {
		if (base[i].fixup == 0) {
			/* A range entry, skip both parts. */
			i++;
			continue;
		}

		/* A deleted entry; see trim_init_extable */
		if (base[i].fixup == -1)
			continue;

		if (base[i].insn == value)
			return &base[i];
	}

	/* 2. Try to find a range match. */
	for (i = 0; i < (num - 1); i++) {
		if (base[i].fixup)
			continue;

		if (base[i].insn <= value && base[i + 1].insn > value)
			return &base[i];

		i++;
	}

        return NULL;
}