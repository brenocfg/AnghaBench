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
struct find_ivrs_hdr_args {int i; int /*<<< orphan*/ * ptr; } ;
typedef  int /*<<< orphan*/  ACPI_IVRS_HARDWARE ;

/* Variables and functions */
 int /*<<< orphan*/  ivrs_hdr_find_iter ; 
 int /*<<< orphan*/  ivrs_hdr_iterate_tbl (int /*<<< orphan*/ ,struct find_ivrs_hdr_args*) ; 

__attribute__((used)) static ACPI_IVRS_HARDWARE *
ivhd_find_by_index(int idx)
{
	struct find_ivrs_hdr_args fi;

	fi.i = idx;
	fi.ptr = NULL;

	ivrs_hdr_iterate_tbl(ivrs_hdr_find_iter, &fi);

	return ((ACPI_IVRS_HARDWARE *)fi.ptr);
}