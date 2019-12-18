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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUBBOCK_SD_IRQ ; 
 int /*<<< orphan*/  lubbock_detect_int ; 
 int /*<<< orphan*/  lubbock_mmc_poll ; 
 int /*<<< orphan*/  mmc_detect_int ; 
 void* mmc_detect_int_data ; 
 int /*<<< orphan*/  mmc_timer ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lubbock_mci_init(struct device *dev,
		irq_handler_t detect_int,
		void *data)
{
	/* detect card insert/eject */
	mmc_detect_int = detect_int;
	mmc_detect_int_data = data;
	timer_setup(&mmc_timer, lubbock_mmc_poll, 0);
	return request_irq(LUBBOCK_SD_IRQ, lubbock_detect_int,
			   0, "lubbock-sd-detect", data);
}