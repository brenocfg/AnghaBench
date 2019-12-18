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
typedef  scalar_t__ u32 ;
struct hwrng {scalar_t__ priv; } ;
struct amd768_priv {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ RNGDATA ; 
 scalar_t__ RNGDONE ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int amd_rng_read(struct hwrng *rng, void *buf, size_t max, bool wait)
{
	u32 *data = buf;
	struct amd768_priv *priv = (struct amd768_priv *)rng->priv;
	size_t read = 0;
	/* We will wait at maximum one time per read */
	int timeout = max / 4 + 1;

	/*
	 * RNG data is available when RNGDONE is set to 1
	 * New random numbers are generated approximately 128 microseconds
	 * after RNGDATA is read
	 */
	while (read < max) {
		if (ioread32(priv->iobase + RNGDONE) == 0) {
			if (wait) {
				/* Delay given by datasheet */
				usleep_range(128, 196);
				if (timeout-- == 0)
					return read;
			} else {
				return 0;
			}
		} else {
			*data = ioread32(priv->iobase + RNGDATA);
			data++;
			read += 4;
		}
	}

	return read;
}