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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,char const*,int) ; 
 int oce_mbox_get_flashrom_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static boolean_t
oce_img_flashing_required(POCE_SOFTC sc, const char *p,
				int img_optype, uint32_t img_offset,
				uint32_t img_size, uint32_t hdrs_size)
{
	uint32_t crc_offset;
	uint8_t flashed_crc[4];
	int status;

	crc_offset = hdrs_size + img_offset + img_size - 4;

	p += crc_offset;

	status = oce_mbox_get_flashrom_crc(sc, flashed_crc,
			(img_size - 4), img_optype);
	if (status)
		return TRUE; /* Some thing worng. ReFlash */

	/*update redboot only if crc does not match*/
	if (bcmp(flashed_crc, p, 4))
		return TRUE;
	else
		return FALSE;
}