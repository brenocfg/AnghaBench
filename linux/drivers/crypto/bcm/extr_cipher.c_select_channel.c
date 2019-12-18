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
typedef  int u8 ;
struct TYPE_3__ {int num_chan; } ;
struct TYPE_4__ {TYPE_1__ spu; int /*<<< orphan*/  next_chan; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 TYPE_2__ iproc_priv ; 

__attribute__((used)) static u8 select_channel(void)
{
	u8 chan_idx = atomic_inc_return(&iproc_priv.next_chan);

	return chan_idx % iproc_priv.spu.num_chan;
}