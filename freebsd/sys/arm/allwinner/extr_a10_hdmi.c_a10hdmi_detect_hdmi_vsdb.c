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

/* Variables and functions */
 int BLOCK_LEN (int) ; 
 int BLOCK_TAG (int) ; 
 int BLOCK_TAG_VSDB ; 
 size_t CEA_DATA_OFF ; 
 int CEA_DATA_START ; 
 int CEA_TAG_ID ; 
 size_t EXT_TAG ; 
 int /*<<< orphan*/  HDMI_OUI ; 
 int /*<<< orphan*/  HDMI_OUI_LEN ; 
 int HDMI_VSDB_MINLEN ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10hdmi_detect_hdmi_vsdb(uint8_t *edid)
{
	int off, p, btag, blen;

	if (edid[EXT_TAG] != CEA_TAG_ID)
		return (0);

	off = edid[CEA_DATA_OFF];

	/* CEA data block collection starts at byte 4 */
	if (off <= CEA_DATA_START)
		return (0);

	/* Parse the CEA data blocks */
	for (p = CEA_DATA_START; p < off;) {
		btag = BLOCK_TAG(edid[p]);
		blen = BLOCK_LEN(edid[p]);

		/* Make sure the length is sane */
		if (p + blen + 1 > off)
			break;

		/* Look for a VSDB with the HDMI 24-bit IEEE registration ID */
		if (btag == BLOCK_TAG_VSDB && blen >= HDMI_VSDB_MINLEN &&
		    memcmp(&edid[p + 1], HDMI_OUI, HDMI_OUI_LEN) == 0)
			return (1);

		/* Next data block */
		p += (1 + blen);
	}

	return (0);
}