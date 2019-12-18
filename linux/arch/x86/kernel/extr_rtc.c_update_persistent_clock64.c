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
struct timespec64 {int dummy; } ;
struct TYPE_2__ {int (* set_wallclock ) (struct timespec64*) ;} ;

/* Variables and functions */
 int stub1 (struct timespec64*) ; 
 TYPE_1__ x86_platform ; 

int update_persistent_clock64(struct timespec64 now)
{
	return x86_platform.set_wallclock(&now);
}