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
struct bwn_mac {int /*<<< orphan*/  mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_ERRPRINTF (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  BWN_NTAB8 (int,int) ; 
 int bwn_nphy_tables_get_antswlut (struct bwn_mac*,int*) ; 
 int /*<<< orphan*/  bwn_ntab_write (struct bwn_mac*,int /*<<< orphan*/ ,int const) ; 
 int nitems (int const*) ; 

__attribute__((used)) static void bwn_nphy_tables_init_rev7_volatile(struct bwn_mac *mac)
{
	int	core, error, offset, i;
	uint8_t	antswlut;

	const int antswlut0_offsets[] = { 0, 4, 8, }; /* Offsets for values */
	const uint8_t antswlut0_values[][3] = {
		{ 0x2, 0x12, 0x8 }, /* Core 0 */
		{ 0x2, 0x18, 0x2 }, /* Core 1 */
	};

	if ((error = bwn_nphy_tables_get_antswlut(mac, &antswlut)))
		return;

	switch (antswlut) {
	case 0:
		for (core = 0; core < 2; core++) {
			for (i = 0; i < nitems(antswlut0_values[0]); i++) {
				offset = core ? 0x20 : 0x00;
				offset += antswlut0_offsets[i];
				bwn_ntab_write(mac, BWN_NTAB8(9, offset),
					       antswlut0_values[core][i]);
			}
		}
		break;
	default:
		BWN_ERRPRINTF(mac->mac_sc, "Unsupported antswlut: %d\n", antswlut);
		break;
	}
}