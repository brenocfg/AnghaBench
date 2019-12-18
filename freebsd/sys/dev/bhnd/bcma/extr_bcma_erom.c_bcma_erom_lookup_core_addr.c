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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_long ;
typedef  scalar_t__ u_int ;
struct bhnd_core_match {int dummy; } ;
struct bhnd_core_info {int dummy; } ;
struct bcma_erom_sport_region {int /*<<< orphan*/  size; int /*<<< orphan*/  base_addr; } ;
struct bcma_erom_core {scalar_t__ num_mport; } ;
struct bcma_erom {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_size_t ;
typedef  scalar_t__ bhnd_port_type ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;
typedef  int /*<<< orphan*/  bhnd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_EROM_ENTRY_IS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BCMA_EROM_GET_ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  REGION ; 
 int /*<<< orphan*/  REGION_PORT ; 
 int /*<<< orphan*/  REGION_TYPE ; 
 int bcma_erom_parse_core (struct bcma_erom*,struct bcma_erom_core*) ; 
 int bcma_erom_parse_sport_region (struct bcma_erom*,struct bcma_erom_sport_region*) ; 
 int bcma_erom_peek32 (struct bcma_erom*,int /*<<< orphan*/ *) ; 
 int bcma_erom_region_to_port_type (struct bcma_erom*,scalar_t__,scalar_t__*) ; 
 int bcma_erom_seek_matching_core (struct bcma_erom*,struct bhnd_core_match const*,struct bhnd_core_info*) ; 
 int bcma_erom_skip_mport (struct bcma_erom*) ; 
 int bcma_erom_skip_sport_region (struct bcma_erom*) ; 

__attribute__((used)) static int
bcma_erom_lookup_core_addr(bhnd_erom_t *erom, const struct bhnd_core_match *desc,
    bhnd_port_type port_type, u_int port_num, u_int region_num,
    struct bhnd_core_info *core, bhnd_addr_t *addr, bhnd_size_t *size)
{
	struct bcma_erom	*sc;
	struct bcma_erom_core	 ec;
	uint32_t		 entry;
	uint8_t			 region_port, region_type;
	bool			 found;
	int			 error;

	sc = (struct bcma_erom *)erom;

	/* Seek to the first matching core and provide the core info
	 * to the caller */
	if ((error = bcma_erom_seek_matching_core(sc, desc, core)))
		return (error);

	if ((error = bcma_erom_parse_core(sc, &ec)))
		return (error);

	/* Skip master ports */
	for (u_long i = 0; i < ec.num_mport; i++) {
		if ((error = bcma_erom_skip_mport(sc)))
			return (error);
	}

	/* Seek to the region block for the given port type */
	found = false;
	while (1) {
		bhnd_port_type	p_type;
		uint8_t		r_type;

		if ((error = bcma_erom_peek32(sc, &entry)))
			return (error);

		if (!BCMA_EROM_ENTRY_IS(entry, REGION))
			return (ENOENT);

		/* Expected region type? */
		r_type = BCMA_EROM_GET_ATTR(entry, REGION_TYPE);
		error = bcma_erom_region_to_port_type(sc, r_type, &p_type);
		if (error)
			return (error);

		if (p_type == port_type) {
			found = true;
			break;
		}

		/* Skip to next entry */
		if ((error = bcma_erom_skip_sport_region(sc)))
			return (error);
	}

	if (!found)
		return (ENOENT);

	/* Found the appropriate port type block; now find the region records
	 * for the given port number */
	found = false;
	for (u_int i = 0; i <= port_num; i++) {
		bhnd_port_type	p_type;

		if ((error = bcma_erom_peek32(sc, &entry)))
			return (error);
		
		if (!BCMA_EROM_ENTRY_IS(entry, REGION))
			return (ENOENT);

		/* Fetch the type/port of the first region entry */
		region_type = BCMA_EROM_GET_ATTR(entry, REGION_TYPE);
		region_port = BCMA_EROM_GET_ATTR(entry, REGION_PORT);

		/* Have we found the region entries for the desired port? */
		if (i == port_num) {
			error = bcma_erom_region_to_port_type(sc, region_type,
			    &p_type);
			if (error)
				return (error);

			if (p_type == port_type)
				found = true;

			break;
		}

		/* Otherwise, seek to next block of region records */
		while (1) {
			uint8_t	next_type, next_port;
	
			if ((error = bcma_erom_skip_sport_region(sc)))
				return (error);

			if ((error = bcma_erom_peek32(sc, &entry)))
				return (error);

			if (!BCMA_EROM_ENTRY_IS(entry, REGION))
				return (ENOENT);

			next_type = BCMA_EROM_GET_ATTR(entry, REGION_TYPE);
			next_port = BCMA_EROM_GET_ATTR(entry, REGION_PORT);

			if (next_type != region_type ||
			    next_port != region_port)
				break;
		}
	}

	if (!found)
		return (ENOENT);

	/* Finally, search for the requested region number */
	for (u_int i = 0; i <= region_num; i++) {
		struct bcma_erom_sport_region	region;
		uint8_t				next_port, next_type;

		if ((error = bcma_erom_peek32(sc, &entry)))
			return (error);
		
		if (!BCMA_EROM_ENTRY_IS(entry, REGION))
			return (ENOENT);

		/* Check for the end of the region block */
		next_type = BCMA_EROM_GET_ATTR(entry, REGION_TYPE);
		next_port = BCMA_EROM_GET_ATTR(entry, REGION_PORT);

		if (next_type != region_type ||
		    next_port != region_port)
			break;

		/* Parse the region */
		if ((error = bcma_erom_parse_sport_region(sc, &region)))
			return (error);

		/* Is this our target region_num? */
		if (i == region_num) {
			/* Found */
			*addr = region.base_addr;
			*size = region.size;
			return (0);
		}
	}

	/* Not found */
	return (ENOENT);
}