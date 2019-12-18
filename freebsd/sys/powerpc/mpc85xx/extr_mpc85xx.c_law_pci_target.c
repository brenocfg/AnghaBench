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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
struct resource {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  SPR_SVR ; 
 int /*<<< orphan*/  SVR_MPC8548 ; 
 int /*<<< orphan*/  SVR_MPC8548E ; 
 int /*<<< orphan*/  SVR_VER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int rman_get_start (struct resource*) ; 

int
law_pci_target(struct resource *res, int *trgt_mem, int *trgt_io)
{
	u_long start;
	uint32_t ver;
	int trgt, rv;

	ver = SVR_VER(mfspr(SPR_SVR));

	start = rman_get_start(res) & 0xf000;

	rv = 0;
	trgt = -1;
	switch (start) {
	case 0x0000:
	case 0x8000:
		trgt = 0;
		break;
	case 0x1000:
	case 0x9000:
		trgt = 1;
		break;
	case 0x2000:
	case 0xa000:
		if (ver == SVR_MPC8548E || ver == SVR_MPC8548)
			trgt = 3;
		else
			trgt = 2;
		break;
	case 0x3000:
	case 0xb000:
		if (ver == SVR_MPC8548E || ver == SVR_MPC8548)
			rv = EINVAL;
		else
			trgt = 3;
		break;
	default:
		rv = ENXIO;
	}
	if (rv == 0) {
		*trgt_mem = trgt;
		*trgt_io = trgt;
	}
	return (rv);
}