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
typedef  size_t u_int32_t ;
struct sc_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ stereo; } ;

/* Variables and functions */
 TYPE_1__* mt ; 
 int /*<<< orphan*/  sv_channel_gain (struct sc_info*,size_t,size_t,int) ; 

__attribute__((used)) static int
sv_gain(struct sc_info *sc, u_int32_t dev, u_int32_t left, u_int32_t right)
{
	sv_channel_gain(sc, dev, left, 0);
	if (mt[dev].stereo)
		sv_channel_gain(sc, dev, right, 1);
	return 0;
}