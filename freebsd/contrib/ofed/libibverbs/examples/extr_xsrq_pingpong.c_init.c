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
struct TYPE_2__ {int size; int ib_port; int num_clients; int num_tests; int gidx; scalar_t__ sl; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_MTU_2048 ; 
 TYPE_1__ ctx ; 
 int getpid () ; 
 int /*<<< orphan*/  srand48 (int) ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init(void)
{
	srand48(getpid() * time(NULL));

	ctx.size = 4096;
	ctx.ib_port = 1;
	ctx.num_clients  = 1;
	ctx.num_tests = 5;
	ctx.mtu = IBV_MTU_2048;
	ctx.sl = 0;
	ctx.gidx = -1;
}