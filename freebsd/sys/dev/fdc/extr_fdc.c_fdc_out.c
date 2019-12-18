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
struct fdc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int FDSTS_TIMEOUT ; 
 int NE7_DIO ; 
 int NE7_RQM ; 
 scalar_t__ bootverbose ; 
 int fdc_err (struct fdc_data*,char*) ; 
 int /*<<< orphan*/  fddata_wr (struct fdc_data*,int) ; 
 int fdsts_rd (struct fdc_data*) ; 

__attribute__((used)) static int
fdc_out(struct fdc_data *fdc, int x)
{
	int i, j, step;

	step = 1;
	for (j = 0; j < FDSTS_TIMEOUT; j += step) {
	        i = fdsts_rd(fdc) & (NE7_DIO | NE7_RQM);
	        if (i == NE7_RQM) {
			fddata_wr(fdc, x);
			return (0);
		}
		if (i == (NE7_DIO|NE7_RQM))
			return (fdc_err(fdc, "ready for input in output\n"));
		step += step;
		DELAY(step);
	}
	return (fdc_err(fdc, bootverbose? "output ready timeout\n": 0));
}