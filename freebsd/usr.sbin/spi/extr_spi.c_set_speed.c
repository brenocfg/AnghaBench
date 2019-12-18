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
typedef  scalar_t__ uint32_t ;
struct spi_options {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIGENIOC_SET_CLOCK_SPEED ; 
 int ioctl (int,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int
set_speed(int hdev, struct spi_options *popt)
{
	uint32_t clock_speed = popt->speed;

	if (popt->speed < 0)
		return 0;

	return ioctl(hdev, SPIGENIOC_SET_CLOCK_SPEED, &clock_speed);
}