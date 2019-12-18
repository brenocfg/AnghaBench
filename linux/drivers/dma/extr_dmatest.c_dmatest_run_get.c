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
struct kernel_param {int dummy; } ;
struct dmatest_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int dmatest_run ; 
 int /*<<< orphan*/  is_threaded_test_pending (struct dmatest_info*) ; 
 scalar_t__ is_threaded_test_run (struct dmatest_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int param_get_bool (char*,struct kernel_param const*) ; 
 int /*<<< orphan*/  stop_threaded_test (struct dmatest_info*) ; 
 struct dmatest_info test_info ; 

__attribute__((used)) static int dmatest_run_get(char *val, const struct kernel_param *kp)
{
	struct dmatest_info *info = &test_info;

	mutex_lock(&info->lock);
	if (is_threaded_test_run(info)) {
		dmatest_run = true;
	} else {
		if (!is_threaded_test_pending(info))
			stop_threaded_test(info);
		dmatest_run = false;
	}
	mutex_unlock(&info->lock);

	return param_get_bool(val, kp);
}