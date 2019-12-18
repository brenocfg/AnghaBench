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
typedef  scalar_t__ uint16_t ;
struct query_cmd {scalar_t__ query_type; scalar_t__ name; } ;

/* Variables and functions */
 struct query_cmd* query_cmds ; 

__attribute__((used)) static const struct query_cmd *find_query_by_type(uint16_t type)
{
	const struct query_cmd *q;

	for (q = query_cmds; q->name; q++)
		if (q->query_type == type)
			return q;

	return NULL;
}