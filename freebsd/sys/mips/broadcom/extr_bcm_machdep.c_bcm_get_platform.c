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
struct bcm_platform {int dummy; } ;

/* Variables and functions */
 struct bcm_platform bcm_platform_data ; 
 int /*<<< orphan*/  bcm_platform_data_avail ; 
 int /*<<< orphan*/  panic (char*) ; 

struct bcm_platform *
bcm_get_platform(void)
{
	if (!bcm_platform_data_avail)
		panic("platform data not available");

	return (&bcm_platform_data);
}