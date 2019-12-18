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
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* get_survey ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int hostapd_drv_get_survey(struct hostapd_data *hapd,
					 unsigned int freq)
{
	if (hapd->driver == NULL)
		return -1;
	if (!hapd->driver->get_survey)
		return -1;
	return hapd->driver->get_survey(hapd->drv_priv, freq);
}