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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t __arraycount (char const**) ; 

__attribute__((used)) static const char *
DeserializeCFICheckKind(uint8_t hhuCFICheckKind)
{
	const char *rgczCFICheckKinds[] = {
		"virtual call",					// CFI_VCALL
		"non-virtual call",				// CFI_NVCALL
		"base-to-derived cast",				// CFI_DERIVEDCAST
		"cast to unrelated type",			// CFI_UNRELATEDCAST
		"indirect function call",			// CFI_ICALL
		"non-virtual pointer to member function call",	// CFI_NVMFCALL
		"virtual pointer to member function call",	// CFI_VMFCALL
	};

	ASSERT(__arraycount(rgczCFICheckKinds) > hhuCFICheckKind);

	return rgczCFICheckKinds[hhuCFICheckKind];
}