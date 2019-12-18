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
 unsigned int HPAGE_16GB_SHIFT ; 
 unsigned int HPAGE_256MB_SHIFT ; 
 unsigned int HPAGE_2GB_SHIFT ; 
 unsigned int HPAGE_64K_SHIFT ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int REAL_HPAGE_SHIFT ; 
#define  _PAGE_SZ16GB_4V 132 
#define  _PAGE_SZ256MB_4V 131 
#define  _PAGE_SZ2GB_4V 130 
#define  _PAGE_SZ4MB_4V 129 
#define  _PAGE_SZ64K_4V 128 
 unsigned long _PAGE_SZALL_4V ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int sun4v_huge_tte_to_shift(pte_t entry)
{
	unsigned long tte_szbits = pte_val(entry) & _PAGE_SZALL_4V;
	unsigned int shift;

	switch (tte_szbits) {
	case _PAGE_SZ16GB_4V:
		shift = HPAGE_16GB_SHIFT;
		break;
	case _PAGE_SZ2GB_4V:
		shift = HPAGE_2GB_SHIFT;
		break;
	case _PAGE_SZ256MB_4V:
		shift = HPAGE_256MB_SHIFT;
		break;
	case _PAGE_SZ4MB_4V:
		shift = REAL_HPAGE_SHIFT;
		break;
	case _PAGE_SZ64K_4V:
		shift = HPAGE_64K_SHIFT;
		break;
	default:
		shift = PAGE_SHIFT;
		break;
	}
	return shift;
}