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
typedef  scalar_t__ uint32_t ;
struct sge_fl {scalar_t__ size; scalar_t__ credits; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  min (int,scalar_t__) ; 
 int /*<<< orphan*/  refill_fl (int /*<<< orphan*/ *,struct sge_fl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
__refill_fl_lt(adapter_t *adap, struct sge_fl *fl, int max)
{
	uint32_t reclaimable = fl->size - fl->credits;

	if (reclaimable > 0)
		refill_fl(adap, fl, min(max, reclaimable));
}