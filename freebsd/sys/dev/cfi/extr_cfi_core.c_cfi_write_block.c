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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int u_int ;
struct cfi_softc {int sc_cmdset; int sc_wrofs; int sc_wrbufsz; int* sc_wrbuf; int* sc_wrbufcpy; int sc_regions; int sc_maxbuf; int sc_width; int /*<<< orphan*/  sc_handle; int /*<<< orphan*/  sc_tag; scalar_t__* sc_max_timeouts; TYPE_1__* sc_region; } ;
typedef  scalar_t__ sbintime_t ;
typedef  int /*<<< orphan*/  register_t ;
struct TYPE_2__ {int r_blksz; } ;

/* Variables and functions */
 int AMD_ADDR_START ; 
 int /*<<< orphan*/  CFI_AMD_BLOCK_ERASE ; 
 int /*<<< orphan*/  CFI_AMD_ERASE_SECTOR ; 
 int CFI_AMD_MAXCHK ; 
 int /*<<< orphan*/  CFI_AMD_PROGRAM ; 
 int /*<<< orphan*/  CFI_BCS_BLOCK_ERASE ; 
 int /*<<< orphan*/  CFI_BCS_BUF_PROG_SETUP ; 
 int /*<<< orphan*/  CFI_BCS_CONFIRM ; 
 int /*<<< orphan*/  CFI_BCS_PROGRAM ; 
 int /*<<< orphan*/  CFI_BCS_READ_ARRAY ; 
 int /*<<< orphan*/  CFI_INTEL_LB ; 
 int /*<<< orphan*/  CFI_INTEL_LBS ; 
 scalar_t__ CFI_INTEL_STATUS_WSMS ; 
 int /*<<< orphan*/  CFI_INTEL_UB ; 
 size_t CFI_TIMEOUT_BUFWRITE ; 
 size_t CFI_TIMEOUT_ERASE ; 
 size_t CFI_TIMEOUT_WRITE ; 
#define  CFI_VEND_AMD_ECS 131 
#define  CFI_VEND_AMD_SCS 130 
#define  CFI_VEND_INTEL_ECS 129 
#define  CFI_VEND_INTEL_SCS 128 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENODEV ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_space_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_write_region_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  bus_space_write_region_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_space_write_region_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  cfi_amd_write (struct cfi_softc*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfi_check_erase (struct cfi_softc*,int,int) ; 
 scalar_t__ cfi_read (struct cfi_softc*,int) ; 
 int /*<<< orphan*/  cfi_reset_default (struct cfi_softc*) ; 
 int cfi_wait_ready (struct cfi_softc*,int,scalar_t__,size_t) ; 
 int /*<<< orphan*/  cfi_write (struct cfi_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffs (int) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sbinuptime () ; 

int
cfi_write_block(struct cfi_softc *sc)
{
	union {
		uint8_t		*x8;
		uint16_t	*x16;
		uint32_t	*x32;
	} ptr, cpyprt;
	register_t intr;
	int error, i, j, neederase = 0;
	uint32_t st;
	u_int wlen;
	sbintime_t start;
	u_int minsz;
	uint32_t val;

	/* Intel flash must be unlocked before modification */
	switch (sc->sc_cmdset) {
	case CFI_VEND_INTEL_ECS:
	case CFI_VEND_INTEL_SCS:
		cfi_write(sc, sc->sc_wrofs, CFI_INTEL_LBS);
		cfi_write(sc, sc->sc_wrofs, CFI_INTEL_UB);
		cfi_write(sc, sc->sc_wrofs, CFI_BCS_READ_ARRAY);
		break;
	}

	/* Check if an erase is required. */
	for (i = 0; i < sc->sc_wrbufsz; i++)
		if ((sc->sc_wrbuf[i] & sc->sc_wrbufcpy[i]) != sc->sc_wrbuf[i]) {
			neederase = 1;
			break;
		}

	if (neederase) {
		intr = intr_disable();
		start = sbinuptime();
		/* Erase the block. */
		switch (sc->sc_cmdset) {
		case CFI_VEND_INTEL_ECS:
		case CFI_VEND_INTEL_SCS:
			cfi_write(sc, sc->sc_wrofs, CFI_BCS_BLOCK_ERASE);
			cfi_write(sc, sc->sc_wrofs, CFI_BCS_CONFIRM);
			break;
		case CFI_VEND_AMD_SCS:
		case CFI_VEND_AMD_ECS:
			/* find minimum sector size */
			minsz = sc->sc_region[0].r_blksz;
			for (i = 1; i < sc->sc_regions; i++) {
				if (sc->sc_region[i].r_blksz < minsz)
					minsz = sc->sc_region[i].r_blksz;
			}
			cfi_amd_write(sc, sc->sc_wrofs, AMD_ADDR_START,
			    CFI_AMD_ERASE_SECTOR);
			cfi_amd_write(sc, sc->sc_wrofs, 
			    sc->sc_wrofs >> (ffs(minsz) - 1),
			    CFI_AMD_BLOCK_ERASE);
			for (i = 0; i < CFI_AMD_MAXCHK; ++i) {
				if (cfi_check_erase(sc, sc->sc_wrofs,
				    sc->sc_wrbufsz))
					break;
				DELAY(10);
			}
			if (i == CFI_AMD_MAXCHK) {
				printf("\nCFI Sector Erase time out error\n");
				return (ENODEV);
			}
			break;
		default:
			/* Better safe than sorry... */
			intr_restore(intr);
			return (ENODEV);
		}
		intr_restore(intr);
		error = cfi_wait_ready(sc, sc->sc_wrofs, start, 
		    CFI_TIMEOUT_ERASE);
		if (error)
			goto out;
	} else
		error = 0;

	/* Write the block using a multibyte write if supported. */
	ptr.x8 = sc->sc_wrbuf;
	cpyprt.x8 = sc->sc_wrbufcpy;
	if (sc->sc_maxbuf > sc->sc_width) {
		switch (sc->sc_cmdset) {
		case CFI_VEND_INTEL_ECS:
		case CFI_VEND_INTEL_SCS:
			for (i = 0; i < sc->sc_wrbufsz; i += wlen) {
				wlen = MIN(sc->sc_maxbuf, sc->sc_wrbufsz - i);

				intr = intr_disable();

				start = sbinuptime();
				do {
					cfi_write(sc, sc->sc_wrofs + i,
					    CFI_BCS_BUF_PROG_SETUP);
					if (sbinuptime() > start + sc->sc_max_timeouts[CFI_TIMEOUT_BUFWRITE]) {
						error = ETIMEDOUT;
						goto out;
					}
					st = cfi_read(sc, sc->sc_wrofs + i);
				} while (! (st & CFI_INTEL_STATUS_WSMS));

				cfi_write(sc, sc->sc_wrofs + i,
				    (wlen / sc->sc_width) - 1);
				switch (sc->sc_width) {
				case 1:
					bus_space_write_region_1(sc->sc_tag,
					    sc->sc_handle, sc->sc_wrofs + i,
					    ptr.x8 + i, wlen);
					break;
				case 2:
					bus_space_write_region_2(sc->sc_tag,
					    sc->sc_handle, sc->sc_wrofs + i,
					    ptr.x16 + i / 2, wlen / 2);
					break;
				case 4:
					bus_space_write_region_4(sc->sc_tag,
					    sc->sc_handle, sc->sc_wrofs + i,
					    ptr.x32 + i / 4, wlen / 4);
					break;
				}

				cfi_write(sc, sc->sc_wrofs + i,
				    CFI_BCS_CONFIRM);

				intr_restore(intr);

				error = cfi_wait_ready(sc, sc->sc_wrofs + i,
				    start, CFI_TIMEOUT_BUFWRITE);
				if (error != 0)
					goto out;
			}
			goto out;
		default:
			/* Fall through to single word case */
			break;
		}

	}

	/* Write the block one byte/word at a time. */
	for (i = 0; i < sc->sc_wrbufsz; i += sc->sc_width) {

		/* Avoid writing unless we are actually changing bits */
		if (!neederase) {
			switch (sc->sc_width) {
			case 1:
				if(*(ptr.x8 + i) == *(cpyprt.x8 + i))
					continue;
				break;
			case 2:
				if(*(ptr.x16 + i / 2) == *(cpyprt.x16 + i / 2))
					continue;
				break;
			case 4:
				if(*(ptr.x32 + i / 4) == *(cpyprt.x32 + i / 4))
					continue;
				break;
			}
		}

		/*
		 * Make sure the command to start a write and the
		 * actual write happens back-to-back without any
		 * excessive delays.
		 */
		intr = intr_disable();

		start = sbinuptime();
		switch (sc->sc_cmdset) {
		case CFI_VEND_INTEL_ECS:
		case CFI_VEND_INTEL_SCS:
			cfi_write(sc, sc->sc_wrofs + i, CFI_BCS_PROGRAM);
			break;
		case CFI_VEND_AMD_SCS:
		case CFI_VEND_AMD_ECS:
			cfi_amd_write(sc, 0, AMD_ADDR_START, CFI_AMD_PROGRAM);
			break;
		}
		switch (sc->sc_width) {
		case 1:
			bus_space_write_1(sc->sc_tag, sc->sc_handle,
			    sc->sc_wrofs + i, *(ptr.x8 + i));
			break;
		case 2:
			bus_space_write_2(sc->sc_tag, sc->sc_handle,
			    sc->sc_wrofs + i, *(ptr.x16 + i / 2));
			break;
		case 4:
			bus_space_write_4(sc->sc_tag, sc->sc_handle,
			    sc->sc_wrofs + i, *(ptr.x32 + i / 4));
			break;
		}
		
		intr_restore(intr);

		if (sc->sc_cmdset == CFI_VEND_AMD_ECS  ||
		    sc->sc_cmdset == CFI_VEND_AMD_SCS) {
			for (j = 0; j < CFI_AMD_MAXCHK; ++j) {
				switch (sc->sc_width) {
				case 1:
					val = *(ptr.x8 + i);
					break;
				case 2:
					val = *(ptr.x16 + i / 2);
					break;
				case 4:
					val = *(ptr.x32 + i / 4);
					break;
				}

				if (cfi_read(sc, sc->sc_wrofs + i) == val)
					break;
					
				DELAY(10);
			}
			if (j == CFI_AMD_MAXCHK) {
				printf("\nCFI Program Verify time out error\n");
				error = ENXIO;
				goto out;
			}
		} else {
			error = cfi_wait_ready(sc, sc->sc_wrofs, start,
			   CFI_TIMEOUT_WRITE);
			if (error)
				goto out;
		}
	}

	/* error is 0. */

 out:
	cfi_reset_default(sc);

	/* Relock Intel flash */
	switch (sc->sc_cmdset) {
	case CFI_VEND_INTEL_ECS:
	case CFI_VEND_INTEL_SCS:
		cfi_write(sc, sc->sc_wrofs, CFI_INTEL_LBS);
		cfi_write(sc, sc->sc_wrofs, CFI_INTEL_LB);
		cfi_write(sc, sc->sc_wrofs, CFI_BCS_READ_ARRAY);
		break;
	}
	return (error);
}