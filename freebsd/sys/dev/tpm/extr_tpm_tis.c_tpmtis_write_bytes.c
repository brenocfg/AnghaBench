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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct tpm_sc {int dummy; } ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,size_t) ; 
 int /*<<< orphan*/  TPM_DATA_FIFO ; 
 int /*<<< orphan*/  WR1 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tpmtis_wait_for_burst (struct tpm_sc*) ; 

__attribute__((used)) static bool
tpmtis_write_bytes(struct tpm_sc *sc, size_t count, uint8_t *buf)
{
	uint16_t burst_count;

	while (count > 0) {
		burst_count = tpmtis_wait_for_burst(sc);
		if (burst_count == 0)
			return (false);

		burst_count = MIN(burst_count, count);
		count -= burst_count;

		while (burst_count-- > 0)
			WR1(sc, TPM_DATA_FIFO, *buf++);
	}

	return (true);
}