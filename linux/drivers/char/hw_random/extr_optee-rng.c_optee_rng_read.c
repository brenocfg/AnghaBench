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
typedef  int /*<<< orphan*/  u8 ;
struct optee_rng_private {int data_rate; } ;
struct hwrng {int dummy; } ;

/* Variables and functions */
 size_t MAX_ENTROPY_REQ_SZ ; 
 size_t get_optee_rng_data (struct optee_rng_private*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct optee_rng_private* to_optee_rng_private (struct hwrng*) ; 

__attribute__((used)) static int optee_rng_read(struct hwrng *rng, void *buf, size_t max, bool wait)
{
	struct optee_rng_private *pvt_data = to_optee_rng_private(rng);
	size_t read = 0, rng_size = 0;
	int timeout = 1;
	u8 *data = buf;

	if (max > MAX_ENTROPY_REQ_SZ)
		max = MAX_ENTROPY_REQ_SZ;

	while (read == 0) {
		rng_size = get_optee_rng_data(pvt_data, data, (max - read));

		data += rng_size;
		read += rng_size;

		if (wait) {
			if (timeout-- == 0)
				return read;
			msleep((1000 * (max - read)) / pvt_data->data_rate);
		} else {
			return read;
		}
	}

	return read;
}