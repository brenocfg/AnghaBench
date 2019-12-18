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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
#define  ACPI_HMAT_ACCESS_LATENCY 130 
#define  ACPI_HMAT_READ_LATENCY 129 
#define  ACPI_HMAT_WRITE_LATENCY 128 
 int DIV_ROUND_UP (int,int) ; 
 int UINT_MAX ; 
 int hmat_revision ; 

__attribute__((used)) static u32 hmat_normalize(u16 entry, u64 base, u8 type)
{
	u32 value;

	/*
	 * Check for invalid and overflow values
	 */
	if (entry == 0xffff || !entry)
		return 0;
	else if (base > (UINT_MAX / (entry)))
		return 0;

	/*
	 * Divide by the base unit for version 1, convert latency from
	 * picosenonds to nanoseconds if revision 2.
	 */
	value = entry * base;
	if (hmat_revision == 1) {
		if (value < 10)
			return 0;
		value = DIV_ROUND_UP(value, 10);
	} else if (hmat_revision == 2) {
		switch (type) {
		case ACPI_HMAT_ACCESS_LATENCY:
		case ACPI_HMAT_READ_LATENCY:
		case ACPI_HMAT_WRITE_LATENCY:
			value = DIV_ROUND_UP(value, 1000);
			break;
		default:
			break;
		}
	}
	return value;
}