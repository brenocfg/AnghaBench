#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct videomode {int dot_clock; } ;
struct TYPE_3__ {int er_max_clock; } ;
struct TYPE_4__ {int /*<<< orphan*/  ec_whitey; int /*<<< orphan*/  ec_whitex; int /*<<< orphan*/  ec_bluey; int /*<<< orphan*/  ec_bluex; int /*<<< orphan*/  ec_greeny; int /*<<< orphan*/  ec_greenx; void* ec_redy; void* ec_redx; } ;
struct edid_info {int edid_product; char* edid_vendorname; char* edid_productname; char* edid_serial; size_t edid_nmodes; char* edid_comment; TYPE_1__ edid_range; scalar_t__ edid_have_range; struct videomode* edid_modes; int /*<<< orphan*/ * edid_preferred_mode; int /*<<< orphan*/  edid_ext_block_count; TYPE_2__ edid_chroma; int /*<<< orphan*/  edid_features; int /*<<< orphan*/  edid_gamma; int /*<<< orphan*/  edid_max_vsize; int /*<<< orphan*/  edid_max_hsize; int /*<<< orphan*/  edid_video_input; int /*<<< orphan*/  edid_revision; int /*<<< orphan*/  edid_version; int /*<<< orphan*/  edid_year; int /*<<< orphan*/  edid_week; int /*<<< orphan*/ * edid_vendor; } ;

/* Variables and functions */
 int EDID_BLOCK_COUNT ; 
 int EDID_BLOCK_SIZE ; 
 int /*<<< orphan*/  EDID_CHROMA_BLUEX (int*) ; 
 int /*<<< orphan*/  EDID_CHROMA_BLUEY (int*) ; 
 int /*<<< orphan*/  EDID_CHROMA_GREENX (int*) ; 
 int /*<<< orphan*/  EDID_CHROMA_GREENY (int*) ; 
 void* EDID_CHROMA_REDX (int*) ; 
 int /*<<< orphan*/  EDID_CHROMA_WHITEX (int*) ; 
 int /*<<< orphan*/  EDID_CHROMA_WHITEY (int*) ; 
 int EDID_EST_TIMING (int*) ; 
 int /*<<< orphan*/  EDID_EXT_BLOCK_COUNT (int*) ; 
 int /*<<< orphan*/  EDID_FEATURES (int*) ; 
 int /*<<< orphan*/  EDID_GAMMA (int*) ; 
 int /*<<< orphan*/  EDID_MANFID_0 (int) ; 
 int /*<<< orphan*/  EDID_MANFID_1 (int) ; 
 int /*<<< orphan*/  EDID_MANFID_2 (int) ; 
 int /*<<< orphan*/  EDID_MAX_HSIZE (int*) ; 
 int /*<<< orphan*/  EDID_MAX_VSIZE (int*) ; 
 int EDID_OFFSET_DESC_BLOCK ; 
 size_t EDID_OFFSET_PRODUCT_ID ; 
 int EDID_OFFSET_STD_TIMING ; 
 int /*<<< orphan*/  EDID_REVISION (int*) ; 
 int EDID_SERIAL_NUMBER (int*) ; 
 int EDID_STD_TIMING_COUNT ; 
 int EDID_VENDOR_ID (int*) ; 
 int /*<<< orphan*/  EDID_VERSION (int*) ; 
 int /*<<< orphan*/  EDID_VIDEO_INPUT (int*) ; 
 int /*<<< orphan*/  EDID_WEEK (int*) ; 
 int /*<<< orphan*/  EDID_YEAR (int*) ; 
 char** _edid_modes ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  edid_block (struct edid_info*,int*) ; 
 char* edid_findproduct (int /*<<< orphan*/ *,int) ; 
 char* edid_findvendor (int /*<<< orphan*/ *) ; 
 scalar_t__ edid_is_valid (int*) ; 
 struct videomode* edid_mode_lookup_list (char*) ; 
 struct videomode* edid_search_mode (struct edid_info*,struct videomode*) ; 
 scalar_t__ edid_std_timing (int*,struct videomode*) ; 
 int /*<<< orphan*/  edid_strchomp (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

int
edid_parse(uint8_t *data, struct edid_info *edid)
{
	uint16_t		manfid, estmodes;
	const struct videomode	*vmp;
	int			i;
	const char		*name;
	int max_dotclock = 0;
	int mhz;

	if (edid_is_valid(data) != 0)
		return -1;

	/* get product identification */
	manfid = EDID_VENDOR_ID(data);
	edid->edid_vendor[0] = EDID_MANFID_0(manfid);
	edid->edid_vendor[1] = EDID_MANFID_1(manfid);
	edid->edid_vendor[2] = EDID_MANFID_2(manfid);
	edid->edid_vendor[3] = 0;	/* null terminate for convenience */

	edid->edid_product = data[EDID_OFFSET_PRODUCT_ID] + 
	    (data[EDID_OFFSET_PRODUCT_ID + 1] << 8);

	name = edid_findvendor(edid->edid_vendor);
	if (name != NULL)
		strlcpy(edid->edid_vendorname, name,
		    sizeof(edid->edid_vendorname));
	else
		edid->edid_vendorname[0] = '\0';

	name = edid_findproduct(edid->edid_vendor, edid->edid_product);
	if (name != NULL)
		strlcpy(edid->edid_productname, name,
		    sizeof(edid->edid_productname));
	else
	    edid->edid_productname[0] = '\0';

	snprintf(edid->edid_serial, sizeof(edid->edid_serial), "%08x",
	    EDID_SERIAL_NUMBER(data));

	edid->edid_week = EDID_WEEK(data);
	edid->edid_year = EDID_YEAR(data);

	/* get edid revision */
	edid->edid_version = EDID_VERSION(data);
	edid->edid_revision = EDID_REVISION(data);

	edid->edid_video_input = EDID_VIDEO_INPUT(data);
	edid->edid_max_hsize = EDID_MAX_HSIZE(data);
	edid->edid_max_vsize = EDID_MAX_VSIZE(data);

	edid->edid_gamma = EDID_GAMMA(data);
	edid->edid_features = EDID_FEATURES(data);

	edid->edid_chroma.ec_redx = EDID_CHROMA_REDX(data);
	edid->edid_chroma.ec_redy = EDID_CHROMA_REDX(data);
	edid->edid_chroma.ec_greenx = EDID_CHROMA_GREENX(data);
	edid->edid_chroma.ec_greeny = EDID_CHROMA_GREENY(data);
	edid->edid_chroma.ec_bluex = EDID_CHROMA_BLUEX(data);
	edid->edid_chroma.ec_bluey = EDID_CHROMA_BLUEY(data);
	edid->edid_chroma.ec_whitex = EDID_CHROMA_WHITEX(data);
	edid->edid_chroma.ec_whitey = EDID_CHROMA_WHITEY(data);

	edid->edid_ext_block_count = EDID_EXT_BLOCK_COUNT(data);

	/* lookup established modes */
	edid->edid_nmodes = 0;
	edid->edid_preferred_mode = NULL;
	estmodes = EDID_EST_TIMING(data);
	/* Iterate in esztablished timing order */
	for (i = 15; i >= 0; i--) {
		if (estmodes & (1 << i)) {
			vmp = edid_mode_lookup_list(_edid_modes[i]);
			if (vmp != NULL) {
				edid->edid_modes[edid->edid_nmodes] = *vmp;
				edid->edid_nmodes++;
			}
#ifdef DIAGNOSTIC
			  else
				printf("no data for est. mode %s\n",
				    _edid_modes[i]);
#endif
		}
	}

	/* do standard timing section */
	for (i = 0; i < EDID_STD_TIMING_COUNT; i++) {
		struct videomode	mode, *exist_mode;
		if (edid_std_timing(data + EDID_OFFSET_STD_TIMING + i * 2,
			&mode)) {
			/* Does this mode already exist? */
			exist_mode = edid_search_mode(edid, &mode);
			if (exist_mode == NULL) {
				edid->edid_modes[edid->edid_nmodes] = mode;
				edid->edid_nmodes++;
			}
		}
	}

	/* do detailed timings and descriptors */
	for (i = 0; i < EDID_BLOCK_COUNT; i++) {
		edid_block(edid, data + EDID_OFFSET_DESC_BLOCK +
		    i * EDID_BLOCK_SIZE);
	}

	edid_strchomp(edid->edid_vendorname);
	edid_strchomp(edid->edid_productname);
	edid_strchomp(edid->edid_serial);
	edid_strchomp(edid->edid_comment);

	/*
	 * XXX
	 * some monitors lie about their maximum supported dot clock
	 * by claiming to support modes which need a higher dot clock
	 * than the stated maximum.
	 * For sanity's sake we bump it to the highest dot clock we find
	 * in the list of supported modes
	 */
	for (i = 0; i < edid->edid_nmodes; i++)
		if (edid->edid_modes[i].dot_clock > max_dotclock)
			max_dotclock = edid->edid_modes[i].dot_clock;
	if (bootverbose) {
		printf("edid: max_dotclock according to supported modes: %d\n",
		    max_dotclock);
	}
	mhz = (max_dotclock + 999) / 1000;

	if (edid->edid_have_range) {
		if (mhz > edid->edid_range.er_max_clock)
			edid->edid_range.er_max_clock = mhz;
	} else
		edid->edid_range.er_max_clock = mhz;

	return 0;
}