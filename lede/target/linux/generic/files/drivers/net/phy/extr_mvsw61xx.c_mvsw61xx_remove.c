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
struct mvsw61xx_state {int /*<<< orphan*/  dev; scalar_t__ registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mvsw61xx_state*) ; 
 struct mvsw61xx_state* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_switch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mvsw61xx_remove(struct platform_device *pdev)
{
	struct mvsw61xx_state *state = platform_get_drvdata(pdev);

	if (state->registered)
		unregister_switch(&state->dev);

	kfree(state);

	return 0;
}