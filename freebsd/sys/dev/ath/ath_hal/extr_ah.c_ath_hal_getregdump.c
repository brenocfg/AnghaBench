#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {scalar_t__ start; scalar_t__ end; } ;
typedef  TYPE_1__ HAL_REGRANGE ;

/* Variables and functions */
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,scalar_t__) ; 

__attribute__((used)) static u_int
ath_hal_getregdump(struct ath_hal *ah, const HAL_REGRANGE *regs,
	void *dstbuf, int space)
{
	uint32_t *dp = dstbuf;
	int i;

	for (i = 0; space >= 2*sizeof(uint32_t); i++) {
		uint32_t r = regs[i].start;
		uint32_t e = regs[i].end;
		*dp++ = r;
		*dp++ = e;
		space -= 2*sizeof(uint32_t);
		do {
			*dp++ = OS_REG_READ(ah, r);
			r += sizeof(uint32_t);
			space -= sizeof(uint32_t);
		} while (r <= e && space >= sizeof(uint32_t));
	}
	return (char *) dp - (char *) dstbuf;
}