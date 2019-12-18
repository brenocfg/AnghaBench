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
struct ipfw_flow_id {scalar_t__ src_ip; scalar_t__ dst_ip; scalar_t__ src_port; scalar_t__ dst_port; } ;

/* Variables and functions */

__attribute__((used)) static __inline int
addrcmp4(const struct ipfw_flow_id *id)
{

	if (id->src_ip < id->dst_ip)
		return (0);
	if (id->src_ip > id->dst_ip)
		return (1);
	if (id->src_port <= id->dst_port)
		return (0);
	return (1);
}