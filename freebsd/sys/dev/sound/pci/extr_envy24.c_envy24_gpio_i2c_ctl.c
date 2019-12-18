#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct envy24_delta_ak4524_codec {TYPE_1__* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SCL_GPIO ; 
 int SDA_GPIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int envy24_gpiord (TYPE_1__*) ; 
 int /*<<< orphan*/  envy24_gpiowr (TYPE_1__*,int) ; 

__attribute__((used)) static void
envy24_gpio_i2c_ctl(void *codec, unsigned int scl, unsigned int sda)
{
        u_int32_t data = 0;
        struct envy24_delta_ak4524_codec *ptr = codec;
#if(0)
        device_printf(ptr->parent->dev, "--> %d, %d\n", scl, sda);
#endif
        data = envy24_gpiord(ptr->parent);
        data &= ~(SDA_GPIO | SCL_GPIO);
        if (scl) data += SCL_GPIO;
        if (sda) data += SDA_GPIO;
        envy24_gpiowr(ptr->parent, data);
        return;
}