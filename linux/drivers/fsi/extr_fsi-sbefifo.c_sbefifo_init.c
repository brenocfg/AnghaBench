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

/* Variables and functions */
 int fsi_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbefifo_drv ; 

__attribute__((used)) static int sbefifo_init(void)
{
	return fsi_driver_register(&sbefifo_drv);
}