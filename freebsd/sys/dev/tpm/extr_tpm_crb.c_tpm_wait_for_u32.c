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
typedef  int uint32_t ;
struct tpm_sc {int dummy; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int RD4 (struct tpm_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 scalar_t__ tick ; 

__attribute__((used)) static bool
tpm_wait_for_u32(struct tpm_sc *sc, bus_size_t off, uint32_t mask, uint32_t val,
    int32_t timeout)
{

	/* Check for condition */
	if ((RD4(sc, off) & mask) == val)
		return (true);

	while (timeout > 0) {
		if ((RD4(sc, off) & mask) == val)
			return (true);

		pause("TPM in polling mode", 1);
		timeout -= tick;
	}
	return (false);
}