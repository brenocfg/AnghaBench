#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  read; int /*<<< orphan*/  name; } ;
struct ccp_device {int /*<<< orphan*/  dev; TYPE_1__ hwrng; int /*<<< orphan*/  rngname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccp_trng_read ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int hwrng_register (TYPE_1__*) ; 

int ccp_register_rng(struct ccp_device *ccp)
{
	int ret = 0;

	dev_dbg(ccp->dev, "Registering RNG...\n");
	/* Register an RNG */
	ccp->hwrng.name = ccp->rngname;
	ccp->hwrng.read = ccp_trng_read;
	ret = hwrng_register(&ccp->hwrng);
	if (ret)
		dev_err(ccp->dev, "error registering hwrng (%d)\n", ret);

	return ret;
}