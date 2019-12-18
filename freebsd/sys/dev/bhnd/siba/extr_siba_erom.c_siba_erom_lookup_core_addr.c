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
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;
struct siba_erom {int /*<<< orphan*/  io; } ;
struct siba_core_id {int dummy; } ;
struct siba_admatch {int am_base; int am_size; } ;
struct bhnd_core_match {int dummy; } ;
struct bhnd_core_info {int /*<<< orphan*/  core_idx; int /*<<< orphan*/  unit; } ;
typedef  int bhnd_size_t ;
typedef  int /*<<< orphan*/  bhnd_port_type ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;
typedef  int bhnd_addr_t ;

/* Variables and functions */
 int BHND_ADDR_MAX ; 
 int /*<<< orphan*/  BHND_PORT_DEVICE ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENXIO ; 
 int SIBA_CFG_OFFSET (scalar_t__) ; 
 int SIBA_CFG_SIZE ; 
 char* bhnd_port_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int siba_addrspace_index (struct siba_core_id*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ siba_admatch_offset (scalar_t__) ; 
 int siba_cfg_index (struct siba_core_id*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 int siba_eio_read_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int siba_eio_read_core_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct siba_core_id*) ; 
 int siba_erom_lookup_core (int /*<<< orphan*/ *,struct bhnd_core_match const*,struct bhnd_core_info*) ; 
 int /*<<< orphan*/  siba_is_port_valid (struct siba_core_id*,int /*<<< orphan*/ ,scalar_t__) ; 
 int siba_parse_admatch (int,struct siba_admatch*) ; 
 scalar_t__ siba_port_region_count (struct siba_core_id*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
siba_erom_lookup_core_addr(bhnd_erom_t *erom, const struct bhnd_core_match *desc,
    bhnd_port_type type, u_int port, u_int region, struct bhnd_core_info *info,
    bhnd_addr_t *addr, bhnd_size_t *size)
{
	struct siba_erom	*sc;
	struct bhnd_core_info	 core;
	struct siba_core_id	 sid;
	struct siba_admatch	 admatch;
	uint32_t		 am;
	u_int			 am_offset;
	u_int			 addrspace, cfg;
	
	int			 error;

	sc = (struct siba_erom *)erom;

	/* Locate the requested core */
	if ((error = siba_erom_lookup_core(erom, desc, &core)))
		return (error);

	/* Fetch full siba core ident */
	error = siba_eio_read_core_id(&sc->io, core.core_idx, core.unit, &sid);
	if (error)
		return (error);

	/* Is port valid? */
	if (!siba_is_port_valid(&sid, type, port))
		return (ENOENT);

	/* Is region valid? */
	if (region >= siba_port_region_count(&sid, type, port))
		return (ENOENT);

	/* Is this a siba configuration region? If so, this is mapped to an
	 * offset within the device0.0 port */
	error = siba_cfg_index(&sid, type, port, region, &cfg);
	if (!error) {
		bhnd_addr_t	region_addr;
		bhnd_addr_t	region_size;
		bhnd_size_t	cfg_offset, cfg_size;

		cfg_offset = SIBA_CFG_OFFSET(cfg);
		cfg_size = SIBA_CFG_SIZE;

		/* Fetch the device0.0 addr/size */
		error = siba_erom_lookup_core_addr(erom, desc, BHND_PORT_DEVICE,
		    0, 0, NULL, &region_addr, &region_size);
		if (error)
			return (error);

		/* Verify that our offset fits within the region */
		if (region_size < cfg_size) {
			printf("%s%u.%u offset %ju exceeds %s0.0 size %ju\n",
			    bhnd_port_type_name(type), port, region, cfg_offset,
			    bhnd_port_type_name(BHND_PORT_DEVICE), region_size);

			return (ENXIO);
		}

		if (BHND_ADDR_MAX - region_addr < cfg_offset) {
			printf("%s%u.%u offset %ju would overflow %s0.0 addr "
			    "%ju\n", bhnd_port_type_name(type), port, region,
			    cfg_offset, bhnd_port_type_name(BHND_PORT_DEVICE),
			    region_addr);

			return (ENXIO);
		}

		if (info != NULL)
			*info = core;

		*addr = region_addr + cfg_offset;
		*size = cfg_size;
		return (0);
	}

	/* 
	 * Otherwise, must be a device port.
	 * 
	 * Map the bhnd device port to a siba addrspace index. Unlike siba(4)
	 * bus drivers, we do not exclude the siba(4) configuration blocks from
	 * the first device port.
	 */
	error = siba_addrspace_index(&sid, type, port, region, &addrspace);
	if (error)
		return (error);

	/* Determine the register offset */
	am_offset = siba_admatch_offset(addrspace);
	if (am_offset == 0) {
		printf("addrspace %u is unsupported", addrspace);
		return (ENODEV);
	}

	/* Read and parse the address match register */
	am = siba_eio_read_4(&sc->io, core.core_idx, am_offset);

	if ((error = siba_parse_admatch(am, &admatch))) {
		printf("failed to decode address match register value 0x%x\n",
		    am);
		return (error);
	}

	if (info != NULL)
		*info = core;

	*addr = admatch.am_base;
	*size = admatch.am_size;

	return (0);
}