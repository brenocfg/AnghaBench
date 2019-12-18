#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int** vpdPdg; scalar_t__** pwrPdg; } ;
typedef  TYPE_1__ CAL_DATA_PER_FREQ_4K ;

/* Variables and functions */
 int AR5416_4K_NUM_PD_GAINS ; 
 int AR5416_PD_GAIN_ICEPTS ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
eeprom_v4k_print_caldata_perfreq(CAL_DATA_PER_FREQ_4K *f)
{
	int i, j;

	for (i = 0; i < AR5416_4K_NUM_PD_GAINS; i++) {
		printf("    Gain %d: pwr dBm/vpd: ", i);
		for (j = 0; j < AR5416_PD_GAIN_ICEPTS; j++) {
			/* These are stored in 0.25dBm increments */
			/* XXX is this assumption correct for ar9285? */
			/* XXX shouldn't we care about the power table offset, if there is one? */
			printf("%d:(%.2f/%d) ", j, (float) f->pwrPdg[i][j] / 4.00,
			    f->vpdPdg[i][j]);
		}
		printf("\n");
	}
}