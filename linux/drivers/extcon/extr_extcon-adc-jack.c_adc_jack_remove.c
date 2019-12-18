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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct adc_jack_data {int /*<<< orphan*/  chan; TYPE_1__ handler; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adc_jack_data*) ; 
 int /*<<< orphan*/  iio_channel_release (int /*<<< orphan*/ ) ; 
 struct adc_jack_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int adc_jack_remove(struct platform_device *pdev)
{
	struct adc_jack_data *data = platform_get_drvdata(pdev);

	free_irq(data->irq, data);
	cancel_work_sync(&data->handler.work);
	iio_channel_release(data->chan);

	return 0;
}