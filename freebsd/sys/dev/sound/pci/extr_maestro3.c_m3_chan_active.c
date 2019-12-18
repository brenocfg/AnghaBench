#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sc_info {int pch_cnt; int rch_cnt; TYPE_2__* rch; TYPE_1__* pch; } ;
struct TYPE_4__ {scalar_t__ active; } ;
struct TYPE_3__ {scalar_t__ active; } ;

/* Variables and functions */

__attribute__((used)) static int
m3_chan_active(struct sc_info *sc)
{
	int i, ret;

	ret = 0;

	for (i = 0; i < sc->pch_cnt; i++)
		ret += sc->pch[i].active;

	for (i = 0; i < sc->rch_cnt; i++)
		ret += sc->rch[i].active;

	return (ret);
}