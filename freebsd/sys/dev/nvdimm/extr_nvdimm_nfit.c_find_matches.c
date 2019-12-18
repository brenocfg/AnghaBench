#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {scalar_t__ Type; scalar_t__ Length; } ;
struct TYPE_5__ {int Length; } ;
struct TYPE_6__ {TYPE_1__ Header; } ;
typedef  TYPE_2__ ACPI_TABLE_NFIT ;
typedef  TYPE_3__ ACPI_NFIT_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  flsl (int /*<<< orphan*/ ) ; 
 int roundup2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
find_matches(ACPI_TABLE_NFIT *nfitbl, uint16_t type, uint16_t offset,
    uint64_t mask, uint64_t value, void **ptrs, int ptrs_len)
{
	ACPI_NFIT_HEADER *h, *end;
	uint64_t val;
	size_t load_size;
	int count;

	h = (ACPI_NFIT_HEADER *)(nfitbl + 1);
	end = (ACPI_NFIT_HEADER *)((char *)nfitbl +
	    nfitbl->Header.Length);
	load_size = roundup2(flsl(mask), 8) / 8;
	count = 0;

	while (h < end) {
		if (h->Type == type) {
			bcopy((char *)h + offset, &val, load_size);
			val &= mask;
			if (val == value) {
				if (ptrs_len > 0) {
					ptrs[count] = h;
					ptrs_len--;
				}
				count++;
			}
		}
		if (h->Length == 0)
			break;
		h = (ACPI_NFIT_HEADER *)((char *)h + h->Length);
	}
	return (count);
}