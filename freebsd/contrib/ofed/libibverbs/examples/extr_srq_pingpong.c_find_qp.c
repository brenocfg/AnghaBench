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
struct pingpong_context {TYPE_1__** qp; } ;
struct TYPE_2__ {int qp_num; } ;

/* Variables and functions */

__attribute__((used)) static int find_qp(int qpn, struct pingpong_context *ctx, int num_qp)
{
	int i;

	for (i = 0; i < num_qp; ++i)
		if (ctx->qp[i]->qp_num == qpn)
			return i;

	return -1;
}