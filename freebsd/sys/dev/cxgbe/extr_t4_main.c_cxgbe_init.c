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
struct vi_info {TYPE_1__* pi; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {struct adapter* adapter; } ;

/* Variables and functions */
 int INTR_OK ; 
 int SLEEP_OK ; 
 scalar_t__ begin_synchronized_op (struct adapter*,struct vi_info*,int,char*) ; 
 int /*<<< orphan*/  cxgbe_init_synchronized (struct vi_info*) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cxgbe_init(void *arg)
{
	struct vi_info *vi = arg;
	struct adapter *sc = vi->pi->adapter;

	if (begin_synchronized_op(sc, vi, SLEEP_OK | INTR_OK, "t4init") != 0)
		return;
	cxgbe_init_synchronized(vi);
	end_synchronized_op(sc, 0);
}