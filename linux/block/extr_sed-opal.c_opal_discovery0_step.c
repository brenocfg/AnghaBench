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
struct opal_step {int /*<<< orphan*/  member_0; } ;
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int execute_step (struct opal_dev*,struct opal_step const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_discovery0 ; 

__attribute__((used)) static int opal_discovery0_step(struct opal_dev *dev)
{
	const struct opal_step discovery0_step = {
		opal_discovery0,
	};

	return execute_step(dev, &discovery0_step, 0);
}