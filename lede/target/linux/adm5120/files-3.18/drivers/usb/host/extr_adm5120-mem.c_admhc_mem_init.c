#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct td {int dummy; } ;
struct ed {int dummy; } ;
struct admhcd {int /*<<< orphan*/ * td_cache; void* ed_cache; } ;
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  ED_ALIGN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TD_ALIGN ; 
 TYPE_2__* admhcd_to_hcd (struct admhcd*) ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int admhc_mem_init(struct admhcd *ahcd)
{
	ahcd->td_cache = dma_pool_create("admhc_td",
		admhcd_to_hcd(ahcd)->self.controller,
		sizeof(struct td),
		TD_ALIGN, /* byte alignment */
		0 /* no page-crossing issues */
		);
	if (!ahcd->td_cache)
		goto err;

	ahcd->ed_cache = dma_pool_create("admhc_ed",
		admhcd_to_hcd(ahcd)->self.controller,
		sizeof(struct ed),
		ED_ALIGN, /* byte alignment */
		0 /* no page-crossing issues */
		);
	if (!ahcd->ed_cache)
		goto err_td_cache;

	return 0;

err_td_cache:
	dma_pool_destroy(ahcd->td_cache);
	ahcd->td_cache = NULL;
err:
	return -ENOMEM;
}