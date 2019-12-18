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

/* Variables and functions */
 int ACPI_PPTT_CACHE_TYPE_UNIFIED ; 
 int ACPI_PPTT_MASK_CACHE_TYPE ; 

__attribute__((used)) static inline bool acpi_pptt_match_type(int table_type, int type)
{
	return ((table_type & ACPI_PPTT_MASK_CACHE_TYPE) == type ||
		table_type & ACPI_PPTT_CACHE_TYPE_UNIFIED & type);
}