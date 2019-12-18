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
typedef  scalar_t__ u32 ;
struct acpi_hest_generic_status {scalar_t__ data_length; scalar_t__ raw_data_length; scalar_t__ raw_data_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 cper_estatus_len(struct acpi_hest_generic_status *estatus)
{
	if (estatus->raw_data_length)
		return estatus->raw_data_offset + \
			estatus->raw_data_length;
	else
		return sizeof(*estatus) + estatus->data_length;
}