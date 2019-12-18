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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct mpr_softc {size_t num_enc_table_entries; struct enc_mapping_table* enclosure_table; } ;
struct enc_mapping_table {scalar_t__ enclosure_id; int phy_bits; } ;

/* Variables and functions */
 size_t MPR_ENCTABLE_BAD_IDX ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
_mapping_get_enc_idx_from_id(struct mpr_softc *sc, u64 enc_id,
    u64 phy_bits)
{
	struct enc_mapping_table *et_entry;
	u8 enc_idx = 0;

	for (enc_idx = 0; enc_idx < sc->num_enc_table_entries; enc_idx++) {
		et_entry = &sc->enclosure_table[enc_idx];
		if ((et_entry->enclosure_id == le64toh(enc_id)) &&
		    (!et_entry->phy_bits || (et_entry->phy_bits &
		    le32toh(phy_bits))))
			return enc_idx;
	}
	return MPR_ENCTABLE_BAD_IDX;
}