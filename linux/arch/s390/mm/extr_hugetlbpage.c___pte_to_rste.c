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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  _PAGE_DIRTY ; 
 int /*<<< orphan*/  _PAGE_INVALID ; 
 int /*<<< orphan*/  _PAGE_NOEXEC ; 
 int /*<<< orphan*/  _PAGE_PROTECT ; 
 int /*<<< orphan*/  _PAGE_READ ; 
 int /*<<< orphan*/  _PAGE_SOFT_DIRTY ; 
 int /*<<< orphan*/  _PAGE_WRITE ; 
 int /*<<< orphan*/  _PAGE_YOUNG ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_DIRTY ; 
 unsigned long _SEGMENT_ENTRY_EMPTY ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_INVALID ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_NOEXEC ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_PROTECT ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_READ ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_SOFT_DIRTY ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_WRITE ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_YOUNG ; 
 unsigned long move_set_bit (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long __pte_to_rste(pte_t pte)
{
	unsigned long rste;

	/*
	 * Convert encoding		  pte bits	pmd / pud bits
	 *				lIR.uswrdy.p	dy..R...I...wr
	 * empty			010.000000.0 -> 00..0...1...00
	 * prot-none, clean, old	111.000000.1 -> 00..1...1...00
	 * prot-none, clean, young	111.000001.1 -> 01..1...1...00
	 * prot-none, dirty, old	111.000010.1 -> 10..1...1...00
	 * prot-none, dirty, young	111.000011.1 -> 11..1...1...00
	 * read-only, clean, old	111.000100.1 -> 00..1...1...01
	 * read-only, clean, young	101.000101.1 -> 01..1...0...01
	 * read-only, dirty, old	111.000110.1 -> 10..1...1...01
	 * read-only, dirty, young	101.000111.1 -> 11..1...0...01
	 * read-write, clean, old	111.001100.1 -> 00..1...1...11
	 * read-write, clean, young	101.001101.1 -> 01..1...0...11
	 * read-write, dirty, old	110.001110.1 -> 10..0...1...11
	 * read-write, dirty, young	100.001111.1 -> 11..0...0...11
	 * HW-bits: R read-only, I invalid
	 * SW-bits: p present, y young, d dirty, r read, w write, s special,
	 *	    u unused, l large
	 */
	if (pte_present(pte)) {
		rste = pte_val(pte) & PAGE_MASK;
		rste |= move_set_bit(pte_val(pte), _PAGE_READ,
				     _SEGMENT_ENTRY_READ);
		rste |= move_set_bit(pte_val(pte), _PAGE_WRITE,
				     _SEGMENT_ENTRY_WRITE);
		rste |= move_set_bit(pte_val(pte), _PAGE_INVALID,
				     _SEGMENT_ENTRY_INVALID);
		rste |= move_set_bit(pte_val(pte), _PAGE_PROTECT,
				     _SEGMENT_ENTRY_PROTECT);
		rste |= move_set_bit(pte_val(pte), _PAGE_DIRTY,
				     _SEGMENT_ENTRY_DIRTY);
		rste |= move_set_bit(pte_val(pte), _PAGE_YOUNG,
				     _SEGMENT_ENTRY_YOUNG);
#ifdef CONFIG_MEM_SOFT_DIRTY
		rste |= move_set_bit(pte_val(pte), _PAGE_SOFT_DIRTY,
				     _SEGMENT_ENTRY_SOFT_DIRTY);
#endif
		rste |= move_set_bit(pte_val(pte), _PAGE_NOEXEC,
				     _SEGMENT_ENTRY_NOEXEC);
	} else
		rste = _SEGMENT_ENTRY_EMPTY;
	return rste;
}