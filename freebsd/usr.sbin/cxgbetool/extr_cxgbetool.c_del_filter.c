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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int prio; int hash; } ;
struct t4_filter {int /*<<< orphan*/  idx; TYPE_1__ fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_DEL_FILTER ; 
 int doit (int /*<<< orphan*/ ,struct t4_filter*) ; 

__attribute__((used)) static int
del_filter(uint32_t idx, int prio, int hashfilter)
{
	struct t4_filter t;

	t.fs.prio = prio;
	t.fs.hash = hashfilter;
	t.idx = idx;

	return doit(CHELSIO_T4_DEL_FILTER, &t);
}