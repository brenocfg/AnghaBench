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
struct atmel_i2c_work_data {int /*<<< orphan*/  work; void* areq; void* cbk; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_i2c_work_handler ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void atmel_i2c_enqueue(struct atmel_i2c_work_data *work_data,
		       void (*cbk)(struct atmel_i2c_work_data *work_data,
				   void *areq, int status),
		       void *areq)
{
	work_data->cbk = (void *)cbk;
	work_data->areq = areq;

	INIT_WORK(&work_data->work, atmel_i2c_work_handler);
	schedule_work(&work_data->work);
}