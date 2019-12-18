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
typedef  int u_int32_t ;
struct sc_info {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int SV_ADC_PLLN (int) ; 
 int SV_ADC_PLLR (int) ; 
 int SV_F_REF ; 
 int SV_F_SCALE ; 
 int /*<<< orphan*/  SV_REG_ADC_PLLM ; 
 int /*<<< orphan*/  SV_REG_ADC_PLLN ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int sv_indirect_get (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv_indirect_set (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sv_set_recspeed(struct sc_info *sc, u_int32_t speed)
{
	u_int32_t	f_out, f_actual;
	u_int32_t	rs, re, r, best_r = 0, r2, t, n, best_n = 0;
	int32_t		m, best_m = 0, ms, me, err, min_err;

	/* This algorithm is a variant described in sonicvibes.pdf
	 * appendix A.  This search is marginally more extensive and
	 * results in (nominally) better sample rate matching. */

	f_out = SV_F_SCALE * speed;
	min_err = 0x7fffffff;

	/* Find bounds of r to examine, rs <= r <= re */
	t = 80000000 / f_out;
	for (rs = 1; (1 << rs) < t; rs++);

	t = 150000000 / f_out;
	for (re = 1; (2 << re) < t; re++);
	if (re > 7) re = 7;

	/* Search over r, n, m */
	for (r = rs; r <= re; r++) {
		r2 = (1 << r);
		for (n = 3; n < 34; n++) {
			m = f_out * n / (SV_F_REF / r2);
			ms = (m > 3) ? (m - 1) : 3;
			me = (m < 129) ? (m + 1) : 129;
			for (m = ms; m <= me; m++) {
				f_actual = m * SV_F_REF / (n * r2);
				if (f_actual > f_out) {
					err = f_actual - f_out;
				} else {
					err = f_out - f_actual;
				}
				if (err < min_err) {
					best_r = r;
					best_m = m - 2;
					best_n = n - 2;
					min_err = err;
					if (err == 0) break;
				}
			}
		}
	}

	sv_indirect_set(sc, SV_REG_ADC_PLLM, best_m);
	sv_indirect_set(sc, SV_REG_ADC_PLLN,
			SV_ADC_PLLN(best_n) | SV_ADC_PLLR(best_r));
	DEB(printf("svrchan_setspeed: %d -> PLLM 0x%02x PLLNR 0x%08x\n",
		   speed,
		   sv_indirect_get(sc, SV_REG_ADC_PLLM),
		   sv_indirect_get(sc, SV_REG_ADC_PLLN)));
	return 0;
}