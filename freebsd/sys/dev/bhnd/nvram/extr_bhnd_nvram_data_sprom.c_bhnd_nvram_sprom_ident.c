#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int* u_char ;
struct bhnd_nvram_io {int dummy; } ;
typedef  int /*<<< orphan*/  srevcrc ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int flags; size_t size; size_t srev_offset; int rev; int /*<<< orphan*/  magic_value; } ;
typedef  TYPE_1__ bhnd_sprom_layout ;

/* Variables and functions */
 int BHND_NVRAM_CRC8_INITIAL ; 
 int BHND_NVRAM_CRC8_VALID ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,size_t,...) ; 
 int /*<<< orphan*/  BHND_NV_PANIC (char*) ; 
 scalar_t__ BHND_NV_VERBOSE ; 
 int ENXIO ; 
 int SPROM_LAYOUT_MAGIC_NONE ; 
 size_t bhnd_nv_ummin (size_t,int) ; 
 int bhnd_nvram_crc8 (int**,size_t,int) ; 
 int bhnd_nvram_io_read (struct bhnd_nvram_io*,size_t,int**,int) ; 
 int bhnd_nvram_sprom_check_magic (struct bhnd_nvram_io*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* bhnd_sprom_layouts ; 
 size_t bhnd_sprom_num_layouts ; 

__attribute__((used)) static int
bhnd_nvram_sprom_ident(struct bhnd_nvram_io *io,
    const bhnd_sprom_layout **ident)
{
	uint8_t	crc;
	size_t	crc_errors;
	size_t	nbytes;
	int	error;

	crc = BHND_NVRAM_CRC8_INITIAL;
	crc_errors = 0;
	nbytes = 0;

	/* We iterate the SPROM layouts smallest to largest, allowing us to
	 * perform incremental checksum calculation */
	for (size_t i = 0; i < bhnd_sprom_num_layouts; i++) {
		const bhnd_sprom_layout	*layout;
		u_char			 buf[512];
		size_t			 nread;
		uint16_t		 magic;
		uint8_t			 srevcrc[2];
		uint8_t			 srev;
		bool			 crc_valid;
		bool			 have_magic;

		layout = &bhnd_sprom_layouts[i];
		crc_valid = true;

		have_magic = true;
		if ((layout->flags & SPROM_LAYOUT_MAGIC_NONE))
			have_magic = false;

		/*
		 * Read image data and update CRC (errors are reported
		 * after the signature check)
		 * 
		 * Layout instances must be ordered from smallest to largest by
		 * the nvram_map compiler, allowing us to incrementally update
		 * our CRC.
		 */
		if (nbytes > layout->size)
			BHND_NV_PANIC("SPROM layout defined out-of-order");

		nread = layout->size - nbytes;

		while (nread > 0) {
			size_t nr;

			nr = bhnd_nv_ummin(nread, sizeof(buf));

			if ((error = bhnd_nvram_io_read(io, nbytes, buf, nr)))
				return (error);

			crc = bhnd_nvram_crc8(buf, nr, crc);
			crc_valid = (crc == BHND_NVRAM_CRC8_VALID);
			if (!crc_valid)
				crc_errors++;

			nread -= nr;
			nbytes += nr;
		}

		/* Read 8-bit SPROM revision, maintaining 16-bit size alignment
		 * required by some OTP/SPROM chipsets. */
		error = bhnd_nvram_io_read(io, layout->srev_offset, &srevcrc,
		    sizeof(srevcrc));
		if (error)
			return (error);

		srev = srevcrc[0];

		/* Early sromrev 1 devices (specifically some BCM440x enet
		 * cards) are reported to have been incorrectly programmed
		 * with a revision of 0x10. */
		if (layout->rev == 1 && srev == 0x10)
			srev = 0x1;
		
		/* Check revision against the layout definition */
		if (srev != layout->rev)
			continue;

		/* Check the magic value, skipping to the next layout on
		 * failure. */
		error = bhnd_nvram_sprom_check_magic(io, layout, &magic);
		if (error) {
			/* If the CRC is was valid, log the mismatch */
			if (crc_valid || BHND_NV_VERBOSE) {
				BHND_NV_LOG("invalid sprom %hhu signature: "
					    "0x%hx (expected 0x%hx)\n", srev,
					    magic, layout->magic_value);

					return (ENXIO);
			}
	
			continue;
		}

		/* Check for an earlier CRC error */
		if (!crc_valid) {
			/* If the magic check succeeded, then we may just have
			 * data corruption -- log the CRC error */
			if (have_magic || BHND_NV_VERBOSE) {
				BHND_NV_LOG("sprom %hhu CRC error (crc=%#hhx, "
					    "expected=%#x)\n", srev, crc,
					    BHND_NVRAM_CRC8_VALID);
			}

			continue;
		}

		/* Identified */
		*ident = layout;
		return (0);
	}

	/* No match */
	if (crc_errors > 0 && BHND_NV_VERBOSE) {
		BHND_NV_LOG("sprom parsing failed with %zu CRC errors\n",
		    crc_errors);
	}

	return (ENXIO);
}