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
struct spi_device {int dummy; } ;
struct moxtet {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unregister ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct moxtet*) ; 
 int /*<<< orphan*/  moxtet_irq_free (struct moxtet*) ; 
 int /*<<< orphan*/  moxtet_unregister_debugfs (struct moxtet*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct moxtet* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int moxtet_remove(struct spi_device *spi)
{
	struct moxtet *moxtet = spi_get_drvdata(spi);

	free_irq(moxtet->dev_irq, moxtet);

	moxtet_irq_free(moxtet);

	moxtet_unregister_debugfs(moxtet);

	device_for_each_child(moxtet->dev, NULL, __unregister);

	mutex_destroy(&moxtet->lock);

	return 0;
}