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
typedef  int uint64_t ;
struct stm_fs {unsigned long mdiv; unsigned long pe; int sdiv; int nsdiv; } ;

/* Variables and functions */
 int P20 ; 
 unsigned long abs (unsigned long) ; 
 int /*<<< orphan*/  clk_fs660c32_dig_get_rate (long,struct stm_fs*,unsigned long*) ; 
 int div64_u64 (int,int) ; 

__attribute__((used)) static int clk_fs660c32_get_pe(int m, int si, unsigned long *deviation,
		signed long input, unsigned long output, uint64_t *p,
		struct stm_fs *fs)
{
	unsigned long new_freq, new_deviation;
	struct stm_fs fs_tmp;
	uint64_t val;

	val = (uint64_t)output << si;

	*p = (uint64_t)input * P20 - (32LL  + (uint64_t)m) * val * (P20 / 32LL);

	*p = div64_u64(*p, val);

	if (*p > 32767LL)
		return 1;

	fs_tmp.mdiv = (unsigned long) m;
	fs_tmp.pe = (unsigned long)*p;
	fs_tmp.sdiv = si;
	fs_tmp.nsdiv = 1;

	clk_fs660c32_dig_get_rate(input, &fs_tmp, &new_freq);

	new_deviation = abs(output - new_freq);

	if (new_deviation < *deviation) {
		fs->mdiv = m;
		fs->pe = (unsigned long)*p;
		fs->sdiv = si;
		fs->nsdiv = 1;
		*deviation = new_deviation;
	}
	return 0;
}