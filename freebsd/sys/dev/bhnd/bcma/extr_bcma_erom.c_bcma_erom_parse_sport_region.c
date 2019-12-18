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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct bcma_erom_sport_region {int base_addr; int size; void* region_port; void* region_type; } ;
struct bcma_erom {int dummy; } ;
typedef  int bhnd_size_t ;
typedef  int bhnd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_EROM_ENTRY_IS (scalar_t__,int /*<<< orphan*/ ) ; 
 void* BCMA_EROM_GET_ATTR (scalar_t__,int /*<<< orphan*/ ) ; 
 int BCMA_EROM_REGION_SIZE_BASE ; 
 int BCMA_EROM_REGION_SIZE_OTHER ; 
 int BHND_ADDR_MAX ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  EROM_LOG (struct bcma_erom*,char*,int /*<<< orphan*/ ,void*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  REGION ; 
 int /*<<< orphan*/  REGION_64BIT ; 
 int /*<<< orphan*/  REGION_BASE ; 
 int /*<<< orphan*/  REGION_PORT ; 
 int /*<<< orphan*/  REGION_SIZE ; 
 int /*<<< orphan*/  REGION_TYPE ; 
 int /*<<< orphan*/  RSIZE_64BIT ; 
 int /*<<< orphan*/  RSIZE_VAL ; 
 int /*<<< orphan*/  bcma_erom_entry_type_name (void*) ; 
 scalar_t__ bcma_erom_peek32 (struct bcma_erom*,scalar_t__*) ; 
 int bcma_erom_read32 (struct bcma_erom*,scalar_t__*) ; 
 int /*<<< orphan*/  bcma_erom_skip32 (struct bcma_erom*) ; 

__attribute__((used)) static int
bcma_erom_parse_sport_region(struct bcma_erom *erom,
    struct bcma_erom_sport_region *region)
{
	uint32_t	entry;
	uint8_t		size_type;
	int		error;

	/* Peek at the region descriptor */
	if (bcma_erom_peek32(erom, &entry))
		return (EINVAL);

	/* A non-region entry signals the end of the region table */
	if (!BCMA_EROM_ENTRY_IS(entry, REGION)) {
		return (ENOENT);
	} else {
		bcma_erom_skip32(erom);
	}

	region->base_addr = BCMA_EROM_GET_ATTR(entry, REGION_BASE);
	region->region_type = BCMA_EROM_GET_ATTR(entry, REGION_TYPE);
	region->region_port = BCMA_EROM_GET_ATTR(entry, REGION_PORT);
	size_type = BCMA_EROM_GET_ATTR(entry, REGION_SIZE);

	/* If region address is 64-bit, fetch the high bits. */
	if (BCMA_EROM_GET_ATTR(entry, REGION_64BIT)) {
		if ((error = bcma_erom_read32(erom, &entry)))
			return (error);
		
		region->base_addr |= ((bhnd_addr_t) entry << 32);
	}

	/* Parse the region size; it's either encoded as the binary logarithm
	 * of the number of 4K pages (i.e. log2 n), or its encoded as a
	 * 32-bit/64-bit literal value directly following the current entry. */
	if (size_type == BCMA_EROM_REGION_SIZE_OTHER) {
		if ((error = bcma_erom_read32(erom, &entry)))
			return (error);

		region->size = BCMA_EROM_GET_ATTR(entry, RSIZE_VAL);

		if (BCMA_EROM_GET_ATTR(entry, RSIZE_64BIT)) {
			if ((error = bcma_erom_read32(erom, &entry)))
				return (error);
			region->size |= ((bhnd_size_t) entry << 32);
		}
	} else {
		region->size = BCMA_EROM_REGION_SIZE_BASE << size_type;
	}

	/* Verify that addr+size does not overflow. */
	if (region->size != 0 &&
	    BHND_ADDR_MAX - (region->size - 1) < region->base_addr)
	{
		EROM_LOG(erom, "%s%u: invalid address map %llx:%llx\n",
		    bcma_erom_entry_type_name(region->region_type),
		    region->region_port,
		    (unsigned long long) region->base_addr,
		    (unsigned long long) region->size);

		return (EINVAL);
	}

	return (0);
}