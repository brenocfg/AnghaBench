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
struct TYPE_4__ {int num_clients; TYPE_1__** recv_qp; } ;
struct TYPE_3__ {int qp_num; } ;

/* Variables and functions */
 TYPE_2__ ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int find_qp(int qpn)
{
	int i;

	if (ctx.num_clients == 1)
		return 0;

	for (i = 0; i < ctx.num_clients; ++i)
		if (ctx.recv_qp[i]->qp_num == qpn)
			return i;

	fprintf(stderr, "Unable to find qp %x\n", qpn);
	return 0;
}