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
typedef  scalar_t__ u_int ;
struct bcma_mport {int /*<<< orphan*/  mp_num; int /*<<< orphan*/  mp_vid; } ;
struct bcma_erom_mport {int /*<<< orphan*/  port_num; int /*<<< orphan*/  port_vid; } ;
struct bcma_erom_core {scalar_t__ vendor; scalar_t__ device; scalar_t__ num_mport; scalar_t__ num_dport; scalar_t__ num_mwrap; scalar_t__ num_swrap; int /*<<< orphan*/  rev; } ;
struct bcma_erom {int dummy; } ;
struct bcma_corecfg {scalar_t__ num_master_ports; scalar_t__ num_dev_ports; scalar_t__ num_bridge_ports; scalar_t__ num_wrapper_ports; int /*<<< orphan*/  master_ports; } ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 scalar_t__ BCMA_EROM_ENTRY_IS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCMA_EROM_ENTRY_TYPE_CORE ; 
 scalar_t__ BCMA_EROM_GET_ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BCMA_EROM_REGION_TYPE_BRIDGE ; 
 scalar_t__ BCMA_EROM_REGION_TYPE_DEVICE ; 
 scalar_t__ BCMA_EROM_REGION_TYPE_MWRAP ; 
 scalar_t__ BCMA_EROM_REGION_TYPE_SWRAP ; 
 scalar_t__ BCMA_PID_MAX ; 
 scalar_t__ BHND_MFGID_BCM ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EROM_LOG (struct bcma_erom*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  REGION ; 
 int /*<<< orphan*/  REGION_TYPE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct bcma_mport*,int /*<<< orphan*/ ) ; 
 struct bcma_corecfg* bcma_alloc_corecfg (scalar_t__,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int bcma_erom_corecfg_fill_port_regions (struct bcma_erom*,struct bcma_corecfg*,scalar_t__,scalar_t__) ; 
 int bcma_erom_parse_core (struct bcma_erom*,struct bcma_erom_core*) ; 
 int bcma_erom_parse_mport (struct bcma_erom*,struct bcma_erom_mport*) ; 
 int bcma_erom_peek32 (struct bcma_erom*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcma_erom_reset (struct bcma_erom*) ; 
 int bcma_erom_seek_next (struct bcma_erom*,int /*<<< orphan*/ ) ; 
 int bcma_erom_skip_core (struct bcma_erom*) ; 
 scalar_t__ bcma_erom_tell (struct bcma_erom*) ; 
 int /*<<< orphan*/  bcma_free_corecfg (struct bcma_corecfg*) ; 
 int /*<<< orphan*/  bhnd_find_core_name (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bhnd_vendor_name (scalar_t__) ; 
 scalar_t__ bootverbose ; 
 struct bcma_mport* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_link ; 

int
bcma_erom_next_corecfg(struct bcma_erom *erom, struct bcma_corecfg **result)
{
	struct bcma_corecfg	*cfg;
	struct bcma_erom_core	 core;
	uint8_t			 first_region_type;
	bus_size_t		 initial_offset;
	u_int			 core_index;
	int			 core_unit;
	int			 error;

	cfg = NULL;
	initial_offset = bcma_erom_tell(erom);

	/* Parse the next core entry */
	if ((error = bcma_erom_parse_core(erom, &core)))
		return (error);

	/* Determine the core's index and unit numbers */
	bcma_erom_reset(erom);
	core_unit = 0;
	core_index = 0;
	for (; bcma_erom_tell(erom) != initial_offset; core_index++) {
		struct bcma_erom_core prev_core;

		/* Parse next core */
		error = bcma_erom_seek_next(erom, BCMA_EROM_ENTRY_TYPE_CORE);
		if (error)
			return (error);

		if ((error = bcma_erom_parse_core(erom, &prev_core)))
			return (error);

		/* Is earlier unit? */
		if (core.vendor == prev_core.vendor &&
		    core.device == prev_core.device)
		{
			core_unit++;
		}

		/* Seek to next core */
		error = bcma_erom_seek_next(erom, BCMA_EROM_ENTRY_TYPE_CORE);
		if (error)
			return (error);
	}

	/* We already parsed the core descriptor */
	if ((error = bcma_erom_skip_core(erom)))
		return (error);

	/* Allocate our corecfg */
	cfg = bcma_alloc_corecfg(core_index, core_unit, core.vendor,
	    core.device, core.rev);
	if (cfg == NULL)
		return (ENOMEM);
	
	/* These are 5-bit values in the EROM table, and should never be able
	 * to overflow BCMA_PID_MAX. */
	KASSERT(core.num_mport <= BCMA_PID_MAX, ("unsupported mport count"));
	KASSERT(core.num_dport <= BCMA_PID_MAX, ("unsupported dport count"));
	KASSERT(core.num_mwrap + core.num_swrap <= BCMA_PID_MAX,
	    ("unsupported wport count"));

	if (bootverbose) {
		EROM_LOG(erom, 
		    "core%u: %s %s (cid=%hx, rev=%hu, unit=%d)\n",
		    core_index,
		    bhnd_vendor_name(core.vendor),
		    bhnd_find_core_name(core.vendor, core.device), 
		    core.device, core.rev, core_unit);
	}

	cfg->num_master_ports = core.num_mport;
	cfg->num_dev_ports = 0;		/* determined below */
	cfg->num_bridge_ports = 0;	/* determined blow */
	cfg->num_wrapper_ports = core.num_mwrap + core.num_swrap;

	/* Parse Master Port Descriptors */
	for (uint8_t i = 0; i < core.num_mport; i++) {
		struct bcma_mport	*mport;
		struct bcma_erom_mport	 mpd;
	
		/* Parse the master port descriptor */
		error = bcma_erom_parse_mport(erom, &mpd);
		if (error)
			goto failed;

		/* Initialize a new bus mport structure */
		mport = malloc(sizeof(struct bcma_mport), M_BHND, M_NOWAIT);
		if (mport == NULL) {
			error = ENOMEM;
			goto failed;
		}
		
		mport->mp_vid = mpd.port_vid;
		mport->mp_num = mpd.port_num;

		/* Update dinfo */
		STAILQ_INSERT_TAIL(&cfg->master_ports, mport, mp_link);
	}
	

	/*
	 * Determine whether this is a bridge device; if so, we can
	 * expect the first sequence of address region descriptors to
	 * be of EROM_REGION_TYPE_BRIDGE instead of
	 * BCMA_EROM_REGION_TYPE_DEVICE.
	 * 
	 * It's unclear whether this is the correct mechanism by which we
	 * should detect/handle bridge devices, but this approach matches
	 * that of (some of) Broadcom's published drivers.
	 */
	if (core.num_dport > 0) {
		uint32_t entry;

		if ((error = bcma_erom_peek32(erom, &entry)))
			goto failed;

		if (BCMA_EROM_ENTRY_IS(entry, REGION) && 
		    BCMA_EROM_GET_ATTR(entry, REGION_TYPE) == BCMA_EROM_REGION_TYPE_BRIDGE)
		{
			first_region_type = BCMA_EROM_REGION_TYPE_BRIDGE;
			cfg->num_dev_ports = 0;
			cfg->num_bridge_ports = core.num_dport;
		} else {
			first_region_type = BCMA_EROM_REGION_TYPE_DEVICE;
			cfg->num_dev_ports = core.num_dport;
			cfg->num_bridge_ports = 0;
		}
	}
	
	/* Device/bridge port descriptors */
	for (uint8_t sp_num = 0; sp_num < core.num_dport; sp_num++) {
		error = bcma_erom_corecfg_fill_port_regions(erom, cfg, sp_num,
		    first_region_type);

		if (error)
			goto failed;
	}

	/* Wrapper (aka device management) descriptors (for master ports). */
	for (uint8_t sp_num = 0; sp_num < core.num_mwrap; sp_num++) {
		error = bcma_erom_corecfg_fill_port_regions(erom, cfg, sp_num,
		    BCMA_EROM_REGION_TYPE_MWRAP);

		if (error)
			goto failed;
	}

	
	/* Wrapper (aka device management) descriptors (for slave ports). */	
	for (uint8_t i = 0; i < core.num_swrap; i++) {
		/* Slave wrapper ports are not numbered distinctly from master
		 * wrapper ports. */

		/* 
		 * Broadcom DDR1/DDR2 Memory Controller
		 * (cid=82e, rev=1, unit=0, d/mw/sw = 2/0/1 ) ->
		 * bhnd0: erom[0xdc]: core6 agent0.0: mismatch got: 0x1 (0x2)
		 *
		 * ARM BP135 AMBA3 AXI to APB Bridge
		 * (cid=135, rev=0, unit=0, d/mw/sw = 1/0/1 ) ->
		 * bhnd0: erom[0x124]: core9 agent1.0: mismatch got: 0x0 (0x2)
		 *
		 * core.num_mwrap
		 * ===>
		 * (core.num_mwrap > 0) ?
		 *           core.num_mwrap :
		 *           ((core.vendor == BHND_MFGID_BCM) ? 1 : 0)
		 */
		uint8_t sp_num;
		sp_num = (core.num_mwrap > 0) ?
				core.num_mwrap :
				((core.vendor == BHND_MFGID_BCM) ? 1 : 0) + i;
		error = bcma_erom_corecfg_fill_port_regions(erom, cfg, sp_num,
		    BCMA_EROM_REGION_TYPE_SWRAP);

		if (error)
			goto failed;
	}

	/*
	 * Seek to the next core entry (if any), skipping any dangling/invalid
	 * region entries.
	 * 
	 * On the BCM4706, the EROM entry for the memory controller core
	 * (0x4bf/0x52E) contains a dangling/unused slave wrapper port region
	 * descriptor.
	 */
	if ((error = bcma_erom_seek_next(erom, BCMA_EROM_ENTRY_TYPE_CORE))) {
		if (error != ENOENT)
			goto failed;
	}

	*result = cfg;
	return (0);
	
failed:
	if (cfg != NULL)
		bcma_free_corecfg(cfg);

	return error;
}