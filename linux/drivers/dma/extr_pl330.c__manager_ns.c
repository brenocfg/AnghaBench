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
struct pl330_thread {TYPE_2__* dmac; } ;
struct TYPE_3__ {int mode; } ;
struct TYPE_4__ {TYPE_1__ pcfg; } ;

/* Variables and functions */
 int DMAC_MODE_NS ; 

__attribute__((used)) static inline bool _manager_ns(struct pl330_thread *thrd)
{
	return (thrd->dmac->pcfg.mode & DMAC_MODE_NS) ? true : false;
}