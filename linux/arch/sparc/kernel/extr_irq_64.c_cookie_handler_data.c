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
typedef  int /*<<< orphan*/  u32 ;
struct irq_handler_data {unsigned int dev_ino; int /*<<< orphan*/  dev_handle; } ;

/* Variables and functions */

__attribute__((used)) static void cookie_handler_data(struct irq_handler_data *data,
				u32 devhandle, unsigned int devino)
{
	data->dev_handle = devhandle;
	data->dev_ino = devino;
}