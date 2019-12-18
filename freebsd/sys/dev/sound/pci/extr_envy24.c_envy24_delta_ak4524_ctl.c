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
struct envy24_delta_ak4524_codec {int cs; int cclk; int cdti; TYPE_1__* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 
 int envy24_gpiord (TYPE_1__*) ; 
 int /*<<< orphan*/  envy24_gpiowr (TYPE_1__*,int) ; 

__attribute__((used)) static void
envy24_delta_ak4524_ctl(void *codec, unsigned int cs, unsigned int cclk, unsigned int cdti)
{
	u_int32_t data = 0;
	struct envy24_delta_ak4524_codec *ptr = codec;

#if(0)
	device_printf(ptr->parent->dev, "--> %d, %d, %d\n", cs, cclk, cdti);
#endif
	data = envy24_gpiord(ptr->parent);
	data &= ~(ptr->cs | ptr->cclk | ptr->cdti);
	if (cs) data += ptr->cs;
	if (cclk) data += ptr->cclk;
	if (cdti) data += ptr->cdti;
	envy24_gpiowr(ptr->parent, data);
	return;
}