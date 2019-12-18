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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MC_REGA ; 
 int /*<<< orphan*/  PC87317_COMMON ; 
 int /*<<< orphan*/  PC87317_RTC ; 
 int /*<<< orphan*/  PC87317_RTC_CR ; 
 int /*<<< orphan*/  RTC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pc87317_setcent(device_t dev, u_int cent)
{

	RTC_WRITE(dev, MC_REGA, PC87317_RTC);
	RTC_WRITE(dev, PC87317_RTC_CR, cent);
	RTC_WRITE(dev, MC_REGA, PC87317_COMMON);
}