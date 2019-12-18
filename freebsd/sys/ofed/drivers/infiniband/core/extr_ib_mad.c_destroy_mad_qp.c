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
struct ib_mad_qp_info {int /*<<< orphan*/  snoop_table; int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_mad_qp(struct ib_mad_qp_info *qp_info)
{
	if (!qp_info->qp)
		return;

	ib_destroy_qp(qp_info->qp);
	kfree(qp_info->snoop_table);
}