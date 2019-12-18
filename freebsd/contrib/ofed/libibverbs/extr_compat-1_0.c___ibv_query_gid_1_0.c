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
typedef  union ibv_gid {int dummy; } ibv_gid ;
typedef  int /*<<< orphan*/  uint8_t ;
struct ibv_context_1_0 {int /*<<< orphan*/  real_context; } ;

/* Variables and functions */
 int ibv_query_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,union ibv_gid*) ; 

int __ibv_query_gid_1_0(struct ibv_context_1_0 *context, uint8_t port_num,
			int index, union ibv_gid *gid)
{
	return ibv_query_gid(context->real_context, port_num, index, gid);
}