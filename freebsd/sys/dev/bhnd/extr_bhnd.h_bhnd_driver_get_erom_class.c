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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  bhnd_erom_class_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BHND_BUS_GET_EROM_CLASS (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bhnd_erom_class_t *
bhnd_driver_get_erom_class(driver_t *driver)
{
	return (BHND_BUS_GET_EROM_CLASS(driver));
}