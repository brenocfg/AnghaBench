#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct resource {scalar_t__ start; scalar_t__ end; int flags; } ;
struct resource_win {scalar_t__ offset; struct resource res; } ;
struct TYPE_5__ {int write_protect; scalar_t__ caching; } ;
struct TYPE_4__ {int /*<<< orphan*/  translation_type; } ;
struct TYPE_6__ {TYPE_2__ mem; TYPE_1__ io; } ;
struct acpi_resource_address {scalar_t__ min_address_fixed; scalar_t__ max_address_fixed; scalar_t__ producer_consumer; int resource_type; TYPE_3__ info; } ;
struct acpi_address64_attribute {int granularity; scalar_t__ address_length; scalar_t__ translation_offset; scalar_t__ minimum; scalar_t__ maximum; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
#define  ACPI_BUS_NUMBER_RANGE 130 
 int /*<<< orphan*/  ACPI_DECODE_10 ; 
 int /*<<< orphan*/  ACPI_DECODE_16 ; 
#define  ACPI_IO_RANGE 129 
#define  ACPI_MEMORY_RANGE 128 
 scalar_t__ ACPI_PREFETCHABLE_MEMORY ; 
 scalar_t__ ACPI_PRODUCER ; 
 int IORESOURCE_BUS ; 
 int IORESOURCE_DISABLED ; 
 int IORESOURCE_PREFETCH ; 
 int IORESOURCE_WINDOW ; 
 int /*<<< orphan*/  acpi_dev_ioresource_flags (struct resource*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dev_memresource_flags (struct resource*,scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool acpi_decode_space(struct resource_win *win,
			      struct acpi_resource_address *addr,
			      struct acpi_address64_attribute *attr)
{
	u8 iodec = attr->granularity == 0xfff ? ACPI_DECODE_10 : ACPI_DECODE_16;
	bool wp = addr->info.mem.write_protect;
	u64 len = attr->address_length;
	u64 start, end, offset = 0;
	struct resource *res = &win->res;

	/*
	 * Filter out invalid descriptor according to ACPI Spec 5.0, section
	 * 6.4.3.5 Address Space Resource Descriptors.
	 */
	if ((addr->min_address_fixed != addr->max_address_fixed && len) ||
	    (addr->min_address_fixed && addr->max_address_fixed && !len))
		pr_debug("ACPI: Invalid address space min_addr_fix %d, max_addr_fix %d, len %llx\n",
			 addr->min_address_fixed, addr->max_address_fixed, len);

	/*
	 * For bridges that translate addresses across the bridge,
	 * translation_offset is the offset that must be added to the
	 * address on the secondary side to obtain the address on the
	 * primary side. Non-bridge devices must list 0 for all Address
	 * Translation offset bits.
	 */
	if (addr->producer_consumer == ACPI_PRODUCER)
		offset = attr->translation_offset;
	else if (attr->translation_offset)
		pr_debug("ACPI: translation_offset(%lld) is invalid for non-bridge device.\n",
			 attr->translation_offset);
	start = attr->minimum + offset;
	end = attr->maximum + offset;

	win->offset = offset;
	res->start = start;
	res->end = end;
	if (sizeof(resource_size_t) < sizeof(u64) &&
	    (offset != win->offset || start != res->start || end != res->end)) {
		pr_warn("acpi resource window ([%#llx-%#llx] ignored, not CPU addressable)\n",
			attr->minimum, attr->maximum);
		return false;
	}

	switch (addr->resource_type) {
	case ACPI_MEMORY_RANGE:
		acpi_dev_memresource_flags(res, len, wp);
		break;
	case ACPI_IO_RANGE:
		acpi_dev_ioresource_flags(res, len, iodec,
					  addr->info.io.translation_type);
		break;
	case ACPI_BUS_NUMBER_RANGE:
		res->flags = IORESOURCE_BUS;
		break;
	default:
		return false;
	}

	if (addr->producer_consumer == ACPI_PRODUCER)
		res->flags |= IORESOURCE_WINDOW;

	if (addr->info.mem.caching == ACPI_PREFETCHABLE_MEMORY)
		res->flags |= IORESOURCE_PREFETCH;

	return !(res->flags & IORESOURCE_DISABLED);
}