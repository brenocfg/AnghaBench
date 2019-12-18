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
struct TYPE_2__ {int /*<<< orphan*/  units; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__ ctlfe_driver ; 
 int /*<<< orphan*/  ctlfeasync ; 
 int /*<<< orphan*/  xpt_register_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctlfeperiphdeinit(void)
{

	/* XXX: It would be good to tear down active ports here. */
	if (!TAILQ_EMPTY(&ctlfe_driver.units))
		return (EBUSY);
	xpt_register_async(0, ctlfeasync, NULL, NULL);
	return (0);
}