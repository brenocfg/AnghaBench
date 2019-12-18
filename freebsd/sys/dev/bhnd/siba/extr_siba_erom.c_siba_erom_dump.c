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
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;
struct TYPE_2__ {scalar_t__ ncores; } ;
struct siba_erom {TYPE_1__ io; } ;
struct siba_admatch {size_t am_base; size_t am_size; } ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDH_DEVICE ; 
 int /*<<< orphan*/  IDH_VENDOR ; 
 int /*<<< orphan*/  IDL_NRADDR ; 
 int /*<<< orphan*/  IDL_SBREV ; 
 scalar_t__ SB0_REG_ABS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIBA_CFG0_IDHIGH ; 
 int /*<<< orphan*/  SIBA_CFG0_IDLOW ; 
 int SIBA_IDH_CORE_REV (int) ; 
 int SIBA_REG_GET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,size_t) ; 
 scalar_t__ siba_admatch_offset (size_t) ; 
 int siba_eio_read_4 (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int siba_parse_admatch (int,struct siba_admatch*) ; 

__attribute__((used)) static int
siba_erom_dump(bhnd_erom_t *erom)
{
	struct siba_erom	*sc;
	int			 error;

	sc = (struct siba_erom *)erom;

	/* Enumerate all cores. */
	for (u_int i = 0; i < sc->io.ncores; i++) {
		uint32_t idhigh, idlow;
		uint32_t nraddr;

		idhigh = siba_eio_read_4(&sc->io, i,
		    SB0_REG_ABS(SIBA_CFG0_IDHIGH));
		idlow = siba_eio_read_4(&sc->io, i,
		    SB0_REG_ABS(SIBA_CFG0_IDLOW));

		printf("siba core %u:\n", i);
		printf("\tvendor:\t0x%04x\n", SIBA_REG_GET(idhigh, IDH_VENDOR));
		printf("\tdevice:\t0x%04x\n", SIBA_REG_GET(idhigh, IDH_DEVICE));
		printf("\trev:\t0x%04x\n", SIBA_IDH_CORE_REV(idhigh));
		printf("\tsbrev:\t0x%02x\n", SIBA_REG_GET(idlow, IDL_SBREV));

		/* Enumerate the address match registers */
		nraddr = SIBA_REG_GET(idlow, IDL_NRADDR);
		printf("\tnraddr\t0x%04x\n", nraddr);

		for (size_t addrspace = 0; addrspace < nraddr; addrspace++) {
			struct siba_admatch	admatch;
			uint32_t		am;
			u_int			am_offset;

			/* Determine the register offset */
			am_offset = siba_admatch_offset(addrspace);
			if (am_offset == 0) {
				printf("addrspace %zu unsupported",
				    addrspace);
				break;
			}
			
			/* Read and parse the address match register */
			am = siba_eio_read_4(&sc->io, i, am_offset);
			if ((error = siba_parse_admatch(am, &admatch))) {
				printf("failed to decode address match "
				    "register value 0x%x\n", am);
				continue;
			}

			printf("\taddrspace %zu\n", addrspace);
			printf("\t\taddr: 0x%08x\n", admatch.am_base);
			printf("\t\tsize: 0x%08x\n", admatch.am_size);
		}
	}

	return (0);
}