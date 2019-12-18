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
struct dc_softc {int* dc_srom; } ;
struct dc_leaf_hdr {int dc_mcnt; } ;
struct dc_eblock_sym {int dummy; } ;
struct dc_eblock_sia {int dummy; } ;
struct dc_eblock_mii {int dummy; } ;
struct dc_eblock_hdr {int dc_type; int dc_len; } ;

/* Variables and functions */
#define  DC_EBLOCK_MII 130 
#define  DC_EBLOCK_SIA 129 
#define  DC_EBLOCK_SYM 128 
 int dc_decode_leaf_mii (struct dc_softc*,struct dc_eblock_mii*) ; 
 int dc_decode_leaf_sia (struct dc_softc*,struct dc_eblock_sia*) ; 
 int dc_decode_leaf_sym (struct dc_softc*,struct dc_eblock_sym*) ; 

__attribute__((used)) static int
dc_parse_21143_srom(struct dc_softc *sc)
{
	struct dc_leaf_hdr *lhdr;
	struct dc_eblock_hdr *hdr;
	int error, have_mii, i, loff;
	char *ptr;

	have_mii = 0;
	loff = sc->dc_srom[27];
	lhdr = (struct dc_leaf_hdr *)&(sc->dc_srom[loff]);

	ptr = (char *)lhdr;
	ptr += sizeof(struct dc_leaf_hdr) - 1;
	/*
	 * Look if we got a MII media block.
	 */
	for (i = 0; i < lhdr->dc_mcnt; i++) {
		hdr = (struct dc_eblock_hdr *)ptr;
		if (hdr->dc_type == DC_EBLOCK_MII)
		    have_mii++;

		ptr += (hdr->dc_len & 0x7F);
		ptr++;
	}

	/*
	 * Do the same thing again. Only use SIA and SYM media
	 * blocks if no MII media block is available.
	 */
	ptr = (char *)lhdr;
	ptr += sizeof(struct dc_leaf_hdr) - 1;
	error = 0;
	for (i = 0; i < lhdr->dc_mcnt; i++) {
		hdr = (struct dc_eblock_hdr *)ptr;
		switch (hdr->dc_type) {
		case DC_EBLOCK_MII:
			error = dc_decode_leaf_mii(sc, (struct dc_eblock_mii *)hdr);
			break;
		case DC_EBLOCK_SIA:
			if (! have_mii)
				error = dc_decode_leaf_sia(sc,
				    (struct dc_eblock_sia *)hdr);
			break;
		case DC_EBLOCK_SYM:
			if (! have_mii)
				error = dc_decode_leaf_sym(sc,
				    (struct dc_eblock_sym *)hdr);
			break;
		default:
			/* Don't care. Yet. */
			break;
		}
		ptr += (hdr->dc_len & 0x7F);
		ptr++;
	}
	return (error);
}