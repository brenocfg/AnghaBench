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
struct sc_chinfo {int /*<<< orphan*/  spd; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  RANGE (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u_int32_t
svchan_setspeed(kobj_t obj, void *data, u_int32_t speed)
{
	struct sc_chinfo *ch = data;
	RANGE(speed, 8000, 48000);
	ch->spd = speed;
	return speed;
}