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
struct device {TYPE_1__* driver; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {scalar_t__ probe_type; } ;

/* Variables and functions */
 scalar_t__ PROBE_PREFER_ASYNCHRONOUS ; 
 int /*<<< orphan*/  TEST_PROBE_DELAY ; 
 int /*<<< orphan*/  async_completed ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dev_to_node (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  errors ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ numa_node_id () ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  warnings ; 

__attribute__((used)) static int test_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	/*
	 * Determine if we have hit the "timeout" limit for the test if we
	 * have then report it as an error, otherwise we wil sleep for the
	 * required amount of time and then report completion.
	 */
	if (atomic_read(&timeout)) {
		dev_err(dev, "async probe took too long\n");
		atomic_inc(&errors);
	} else {
		dev_dbg(&pdev->dev, "sleeping for %d msecs in probe\n",
			 TEST_PROBE_DELAY);
		msleep(TEST_PROBE_DELAY);
		dev_dbg(&pdev->dev, "done sleeping\n");
	}

	/*
	 * Report NUMA mismatch if device node is set and we are not
	 * performing an async init on that node.
	 */
	if (dev->driver->probe_type == PROBE_PREFER_ASYNCHRONOUS) {
		if (dev_to_node(dev) != numa_node_id()) {
			dev_warn(dev, "NUMA node mismatch %d != %d\n",
				 dev_to_node(dev), numa_node_id());
			atomic_inc(&warnings);
		}

		atomic_inc(&async_completed);
	}

	return 0;
}