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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t u_int ;
struct sun_disklabel {size_t sl_rpm; size_t sl_pcylinders; size_t sl_sparespercyl; size_t sl_interleave; size_t sl_ncylinders; size_t sl_acylinders; size_t sl_ntracks; size_t sl_nsectors; size_t sl_magic; scalar_t__ sl_vtoc_sane; size_t sl_vtoc_nparts; scalar_t__ sl_vtoc_vers; TYPE_2__* sl_vtoc_map; int /*<<< orphan*/  sl_vtoc_volname; TYPE_1__* sl_part; int /*<<< orphan*/ * sl_text; } ;
struct TYPE_4__ {size_t svtoc_tag; size_t svtoc_flag; } ;
struct TYPE_3__ {scalar_t__ sdkp_cyloffset; scalar_t__ sdkp_nsectors; } ;

/* Variables and functions */
 int SDKP_CYLOFFSET ; 
 int SDKP_NSECTORS ; 
 size_t SDKP_SIZEOF ; 
 int SL_ACYLINDERS ; 
 int SL_CKSUM ; 
 int SL_INTERLEAVE ; 
 int SL_MAGIC ; 
 int SL_NCYLINDERS ; 
 int SL_NSECTORS ; 
 int SL_NTRACKS ; 
 int SL_PART ; 
 int SL_PCYLINDERS ; 
 int SL_RPM ; 
 int SL_SPARESPERCYL ; 
 size_t SL_TEXT ; 
 size_t SL_TEXT_SIZEOF ; 
 int SL_VTOC_MAP ; 
 int SL_VTOC_NPART ; 
 int SL_VTOC_SANITY ; 
 int SL_VTOC_VERS ; 
 int SL_VTOC_VOLNAME ; 
 size_t SUN_NPART ; 
 size_t SUN_SIZE ; 
 int /*<<< orphan*/  SUN_VOLNAME_LEN ; 
 scalar_t__ SUN_VTOC_SANE ; 
 int SVTOC_FLAG ; 
 size_t SVTOC_SIZEOF ; 
 int SVTOC_TAG ; 
 size_t be16dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be16enc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  be32enc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sunlabel_enc(void *pp, struct sun_disklabel *sl)
{
	uint8_t *p;
	size_t i;
	u_int u;

	p = pp;
	for (i = 0; i < SL_TEXT_SIZEOF; i++)
		p[SL_TEXT + i] = sl->sl_text[i];
	be16enc(p + SL_RPM, sl->sl_rpm);
	be16enc(p + SL_PCYLINDERS, sl->sl_pcylinders);
	be16enc(p + SL_SPARESPERCYL, sl->sl_sparespercyl);
	be16enc(p + SL_INTERLEAVE, sl->sl_interleave);
	be16enc(p + SL_NCYLINDERS, sl->sl_ncylinders);
	be16enc(p + SL_ACYLINDERS, sl->sl_acylinders);
	be16enc(p + SL_NTRACKS, sl->sl_ntracks);
	be16enc(p + SL_NSECTORS, sl->sl_nsectors);
	for (i = 0; i < SUN_NPART; i++) {
		be32enc(p + SL_PART + (i * SDKP_SIZEOF) + SDKP_CYLOFFSET,
		    sl->sl_part[i].sdkp_cyloffset);
		be32enc(p + SL_PART + (i * SDKP_SIZEOF) + SDKP_NSECTORS,
		    sl->sl_part[i].sdkp_nsectors);
	}
	be16enc(p + SL_MAGIC, sl->sl_magic);
	if (sl->sl_vtoc_sane == SUN_VTOC_SANE
	    && sl->sl_vtoc_nparts == SUN_NPART) {
		/*
		 * Write SVR4-compatible VTOC elements.
		 */
		be32enc(p + SL_VTOC_VERS, sl->sl_vtoc_vers);
		be32enc(p + SL_VTOC_SANITY, SUN_VTOC_SANE);
		memcpy(p + SL_VTOC_VOLNAME, sl->sl_vtoc_volname,
		    SUN_VOLNAME_LEN);
		be16enc(p + SL_VTOC_NPART, SUN_NPART);
		for (i = 0; i < SUN_NPART; i++) {
			be16enc(p + SL_VTOC_MAP + (i * SVTOC_SIZEOF)
				+ SVTOC_TAG,
				sl->sl_vtoc_map[i].svtoc_tag);
			be16enc(p + SL_VTOC_MAP + (i * SVTOC_SIZEOF)
				+ SVTOC_FLAG,
				sl->sl_vtoc_map[i].svtoc_flag);
		}
	}
	for (i = u = 0; i < SUN_SIZE; i += 2)
		u ^= be16dec(p + i);
	be16enc(p + SL_CKSUM, u);
}