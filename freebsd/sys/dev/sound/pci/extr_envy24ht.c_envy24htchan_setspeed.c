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
typedef  int u_int32_t ;
struct sc_chinfo {int speed; TYPE_1__* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int* envy24ht_speed ; 

__attribute__((used)) static u_int32_t
envy24htchan_setspeed(kobj_t obj, void *data, u_int32_t speed)
{
	struct sc_chinfo *ch = data;
	u_int32_t val, prev;
	int i;

#if(0)
	device_printf(ch->parent->dev, "envy24htchan_setspeed(obj, data, %d)\n", speed);
#endif
	prev = 0x7fffffff;
	for (i = 0; (val = envy24ht_speed[i]) != 0; i++) {
		if (abs(val - speed) < abs(prev - speed))
			prev = val;
		else
			break;
	}
	ch->speed = prev;
	
#if(0)
	device_printf(ch->parent->dev, "envy24htchan_setspeed(): return %d\n", ch->speed);
#endif
	return ch->speed;
}