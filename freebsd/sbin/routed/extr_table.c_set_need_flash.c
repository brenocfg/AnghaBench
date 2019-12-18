#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ MIN_WAITTIME ; 
 int need_flash ; 
 TYPE_2__ no_flash ; 
 TYPE_1__ now ; 

__attribute__((used)) static void
set_need_flash(void)
{
	if (!need_flash) {
		need_flash = 1;
		/* Do not send the flash update immediately.  Wait a little
		 * while to hear from other routers.
		 */
		no_flash.tv_sec = now.tv_sec + MIN_WAITTIME;
	}
}