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
typedef  unsigned int uint32_t ;
struct fsl_sata_channel {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 unsigned int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 

__attribute__((used)) static int
fsl_sata_wait_register(struct fsl_sata_channel *ch, bus_size_t off,
    unsigned int mask, unsigned int val, int t)
{
	int timeout = 0;
	uint32_t rval;

	while (((rval = ATA_INL(ch->r_mem, off)) & mask) != val) {
		if (timeout > t) {
			return (EBUSY);
		}
		DELAY(1000);
		timeout++;
	}
	return (0);
}