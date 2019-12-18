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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24_CCI_GPIOCTL ; 
 int /*<<< orphan*/  envy24_wrci (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
envy24_gpiosetdir(struct sc_info *sc, u_int32_t dir)
{
	envy24_wrci(sc, ENVY24_CCI_GPIOCTL, dir);
	return;
}