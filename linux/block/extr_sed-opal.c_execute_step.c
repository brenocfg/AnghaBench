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
struct opal_step {int (* fn ) (struct opal_dev*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  opal_error_to_human (int) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,int (*) (struct opal_dev*,int /*<<< orphan*/ ),int,int /*<<< orphan*/ ) ; 
 int stub1 (struct opal_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execute_step(struct opal_dev *dev,
			const struct opal_step *step, size_t stepIndex)
{
	int error = step->fn(dev, step->data);

	if (error) {
		pr_debug("Step %zu (%pS) failed with error %d: %s\n",
			 stepIndex, step->fn, error,
			 opal_error_to_human(error));
	}

	return error;
}