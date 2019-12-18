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
struct n2rng {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int EPERM ; 
 int EWOULDBLOCK ; 
 unsigned long HV_EIO ; 
 unsigned long HV_ENOACCESS ; 
 unsigned long HV_EOK ; 
 unsigned long HV_EWOULDBLOCK ; 
 int N2RNG_BLOCK_LIMIT ; 
 int /*<<< orphan*/  __delay (unsigned long) ; 
 unsigned long n2rng_read_diag_data_one (struct n2rng*,unsigned long,unsigned long,unsigned long,unsigned long*) ; 

__attribute__((used)) static int n2rng_generic_read_diag_data(struct n2rng *np,
					unsigned long unit,
					unsigned long data_ra,
					unsigned long data_len)
{
	unsigned long ticks, hv_err;
	int block = 0;

	while (1) {
		hv_err = n2rng_read_diag_data_one(np, unit,
						  data_ra, data_len,
						  &ticks);
		if (hv_err == HV_EOK)
			return 0;

		if (hv_err == HV_EWOULDBLOCK) {
			if (++block >= N2RNG_BLOCK_LIMIT)
				return -EWOULDBLOCK;
			__delay(ticks);
		} else if (hv_err == HV_ENOACCESS) {
			return -EPERM;
		} else if (hv_err == HV_EIO) {
			return -EIO;
		} else
			return -ENODEV;
	}
}