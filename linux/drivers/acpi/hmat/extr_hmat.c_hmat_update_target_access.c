#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  void* u32 ;
struct TYPE_2__ {void* write_bandwidth; void* read_bandwidth; void* write_latency; void* read_latency; } ;
struct memory_target {TYPE_1__ hmem_attrs; } ;

/* Variables and functions */
#define  ACPI_HMAT_ACCESS_BANDWIDTH 133 
#define  ACPI_HMAT_ACCESS_LATENCY 132 
#define  ACPI_HMAT_READ_BANDWIDTH 131 
#define  ACPI_HMAT_READ_LATENCY 130 
#define  ACPI_HMAT_WRITE_BANDWIDTH 129 
#define  ACPI_HMAT_WRITE_LATENCY 128 

__attribute__((used)) static void hmat_update_target_access(struct memory_target *target,
					     u8 type, u32 value)
{
	switch (type) {
	case ACPI_HMAT_ACCESS_LATENCY:
		target->hmem_attrs.read_latency = value;
		target->hmem_attrs.write_latency = value;
		break;
	case ACPI_HMAT_READ_LATENCY:
		target->hmem_attrs.read_latency = value;
		break;
	case ACPI_HMAT_WRITE_LATENCY:
		target->hmem_attrs.write_latency = value;
		break;
	case ACPI_HMAT_ACCESS_BANDWIDTH:
		target->hmem_attrs.read_bandwidth = value;
		target->hmem_attrs.write_bandwidth = value;
		break;
	case ACPI_HMAT_READ_BANDWIDTH:
		target->hmem_attrs.read_bandwidth = value;
		break;
	case ACPI_HMAT_WRITE_BANDWIDTH:
		target->hmem_attrs.write_bandwidth = value;
		break;
	default:
		break;
	}
}