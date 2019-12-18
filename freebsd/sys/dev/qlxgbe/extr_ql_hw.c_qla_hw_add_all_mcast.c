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
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int qla_hw_all_mcast (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
qla_hw_add_all_mcast(qla_host_t *ha)
{
	int ret;

	ret = qla_hw_all_mcast(ha, 1);

	return (ret);
}