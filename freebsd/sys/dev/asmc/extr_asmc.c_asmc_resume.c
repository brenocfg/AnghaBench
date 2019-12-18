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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASMC_KEY_LIGHTVALUE ; 
 int /*<<< orphan*/  asmc_key_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int light_control ; 

__attribute__((used)) static int
asmc_resume(device_t dev)
{
    uint8_t buf[2];
    buf[0] = light_control;
    buf[1] = 0x00;
    asmc_key_write(dev, ASMC_KEY_LIGHTVALUE, buf, sizeof buf);
    return (0);
}