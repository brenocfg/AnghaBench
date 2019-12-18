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
struct cal_data_op_loop_ar9287 {int** pwrPdg; int** vpdPdg; int** pcdac; int** empty; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
eeprom_9287_print_caldata_oploop(struct cal_data_op_loop_ar9287 *f)
{
	int i, j;

	/* XXX flesh out the rest */
	for (i = 0; i < 2; i++) {
		printf("    pwrPdg:");
		for (j = 0; j < 5; j++) {
			printf("[%d][%d]=%d, ", i, j, f->pwrPdg[i][j]);
		}
		printf("\n");

		printf("    vpdPdg:");
		for (j = 0; j < 5; j++) {
			printf("[%d][%d]=%d, ", i, j, f->vpdPdg[i][j]);
		}
		printf("\n");

		printf("    pcdac:");
		for (j = 0; j < 5; j++) {
			printf("[%d][%d]=%d, ", i, j, f->pcdac[i][j]);
		}
		printf("\n");

		printf("    empty:");
		for (j = 0; j < 5; j++) {
			printf("[%d][%d]=%d, ", i, j, f->empty[i][j]);
		}
		printf("\n\n");
	}
}