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
struct platform_device {int dummy; } ;
struct n2rng {int /*<<< orphan*/  work; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_GRP_RNG ; 
 int /*<<< orphan*/  N2RNG_FLAG_SHUTDOWN ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct n2rng* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sun4v_hvapi_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int n2rng_remove(struct platform_device *op)
{
	struct n2rng *np = platform_get_drvdata(op);

	np->flags |= N2RNG_FLAG_SHUTDOWN;

	cancel_delayed_work_sync(&np->work);

	sun4v_hvapi_unregister(HV_GRP_RNG);

	return 0;
}