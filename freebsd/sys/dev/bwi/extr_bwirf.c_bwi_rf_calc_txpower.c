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
typedef  int const uint8_t ;
typedef  int int8_t ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int EINVAL ; 
 int ITER_MAX ; 
 int _bwi_adjust_devide (int,int) ; 
 int abs (int) ; 
 int imax (int,int) ; 

__attribute__((used)) static int
bwi_rf_calc_txpower(int8_t *txpwr, uint8_t idx, const int16_t pa_params[])
{
	int32_t m1, m2, f, dbm;
	int i;

	m1 = _bwi_adjust_devide(16 * pa_params[0] + idx * pa_params[1], 32);
	m2 = imax(_bwi_adjust_devide(32768 + idx * pa_params[2], 256), 1);

#define ITER_MAX	16

	f = 256;
	for (i = 0; i < ITER_MAX; ++i) {
		int32_t q, d;

		q = _bwi_adjust_devide(
			f * 4096 - _bwi_adjust_devide(m2 * f, 16) * f, 2048);
		d = abs(q - f);
		f = q;

		if (d < 2)
			break;
	}
	if (i == ITER_MAX)
		return EINVAL;

#undef ITER_MAX

	dbm = _bwi_adjust_devide(m1 * f, 8192);
	if (dbm < -127)
		dbm = -127;
	else if (dbm > 128)
		dbm = 128;

	*txpwr = dbm;
	return 0;
}