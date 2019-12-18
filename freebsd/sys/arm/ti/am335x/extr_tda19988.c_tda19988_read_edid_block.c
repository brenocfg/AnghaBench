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
struct tda19988_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDID_LENGTH ; 
 int INT_FLAGS_2_EDID_BLK_RD ; 
 int MAX_READ_ATTEMPTS ; 
 int /*<<< orphan*/  TDA_DDC_ADDR ; 
 int /*<<< orphan*/  TDA_DDC_OFFS ; 
 int /*<<< orphan*/  TDA_DDC_SEGM ; 
 int /*<<< orphan*/  TDA_DDC_SEGM_ADDR ; 
 int /*<<< orphan*/  TDA_EDID_CTRL ; 
 int /*<<< orphan*/  TDA_EDID_DATA0 ; 
 int /*<<< orphan*/  TDA_INT_FLAGS_2 ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 scalar_t__ tda19988_block_read (struct tda19988_softc*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda19988_reg_clear (struct tda19988_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda19988_reg_read (struct tda19988_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tda19988_reg_set (struct tda19988_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda19988_reg_write (struct tda19988_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
tda19988_read_edid_block(struct tda19988_softc *sc, uint8_t *buf, int block)
{
	int attempt, err;
	uint8_t data;

	err = 0;

	tda19988_reg_set(sc, TDA_INT_FLAGS_2, INT_FLAGS_2_EDID_BLK_RD);

	/* Block 0 */
	tda19988_reg_write(sc, TDA_DDC_ADDR, 0xa0);
	tda19988_reg_write(sc, TDA_DDC_OFFS, (block % 2) ? 128 : 0);
	tda19988_reg_write(sc, TDA_DDC_SEGM_ADDR, 0x60);
	tda19988_reg_write(sc, TDA_DDC_SEGM, block / 2);

	tda19988_reg_write(sc, TDA_EDID_CTRL, 1);
	tda19988_reg_write(sc, TDA_EDID_CTRL, 0);

	data = 0;
	for (attempt = 0; attempt < MAX_READ_ATTEMPTS; attempt++) {
		tda19988_reg_read(sc, TDA_INT_FLAGS_2, &data);
		if (data & INT_FLAGS_2_EDID_BLK_RD)
			break;
		pause("EDID", 1);
	}

	if (attempt == MAX_READ_ATTEMPTS) {
		err = -1;
		goto done;
	}

	if (tda19988_block_read(sc, TDA_EDID_DATA0, buf, EDID_LENGTH) != 0) {
		err = -1;
		goto done;
	}

done:
	tda19988_reg_clear(sc, TDA_INT_FLAGS_2, INT_FLAGS_2_EDID_BLK_RD);

	return (err);
}