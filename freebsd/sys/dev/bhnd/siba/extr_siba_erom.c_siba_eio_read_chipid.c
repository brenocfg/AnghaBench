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
struct siba_erom_io {int /*<<< orphan*/  eio; } ;
struct TYPE_2__ {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  hwrev; } ;
struct siba_core_id {TYPE_1__ core_info; } ;
struct bhnd_chipid {int chip_id; int ncores; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
#define  BHND_CHIPID_BCM4306 130 
#define  BHND_CHIPID_BCM4704 129 
#define  BHND_CHIPID_BCM5365 128 
 scalar_t__ BHND_COREID_CC ; 
 scalar_t__ BHND_MFGID_BCM ; 
 scalar_t__ CHIPC_NCORES_MIN_HWREV (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  EROM_LOG (struct siba_erom_io*,char*,scalar_t__,scalar_t__) ; 
 int bhnd_erom_read_chipid (int /*<<< orphan*/ ,struct bhnd_chipid*) ; 
 scalar_t__ bootverbose ; 
 int siba_eio_read_core_id (struct siba_erom_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct siba_core_id*) ; 

__attribute__((used)) static int
siba_eio_read_chipid(struct siba_erom_io *io, bus_addr_t enum_addr,
    struct bhnd_chipid *cid)
{
	struct siba_core_id	ccid;
	int			error;

	/* Identify the chipcommon core */
	if ((error = siba_eio_read_core_id(io, 0, 0, &ccid)))
		return (error);

	if (ccid.core_info.vendor != BHND_MFGID_BCM ||
	    ccid.core_info.device != BHND_COREID_CC)
	{
		if (bootverbose) {
			EROM_LOG(io, "first core not chipcommon "
			    "(vendor=%#hx, core=%#hx)\n", ccid.core_info.vendor,
			    ccid.core_info.device);
		}
		return (ENXIO);
	}

	/* Identify the chipset */
	if ((error = bhnd_erom_read_chipid(io->eio, cid)))
		return (error);

	/* Do we need to fix up the core count? */
	if (CHIPC_NCORES_MIN_HWREV(ccid.core_info.hwrev))
		return (0);

	switch (cid->chip_id) {
	case BHND_CHIPID_BCM4306:
		cid->ncores = 6;
		break;
	case BHND_CHIPID_BCM4704:
		cid->ncores = 9;
		break;
	case BHND_CHIPID_BCM5365:
		/*
		* BCM5365 does support ID_NUMCORE in at least
		* some of its revisions, but for unknown
		* reasons, Broadcom's drivers always exclude
		* the ChipCommon revision (0x5) used by BCM5365
		* from the set of revisions supporting
		* ID_NUMCORE, and instead supply a fixed value.
		* 
		* Presumably, at least some of these devices
		* shipped with a broken ID_NUMCORE value.
		*/
		cid->ncores = 7;
		break;
	default:
		return (EINVAL);
	}

	return (0);
}