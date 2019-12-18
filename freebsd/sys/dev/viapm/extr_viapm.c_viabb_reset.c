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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_ENOADDR ; 
 int /*<<< orphan*/  viabb_setscl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  viabb_setsda (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
viabb_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	/* reset bus */
	viabb_setsda(dev, 1);
	viabb_setscl(dev, 1);

	return (IIC_ENOADDR);
}