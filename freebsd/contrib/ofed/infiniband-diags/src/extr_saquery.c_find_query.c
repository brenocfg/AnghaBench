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
struct query_cmd {scalar_t__ alias; scalar_t__ name; } ;

/* Variables and functions */
 struct query_cmd* query_cmds ; 
 int /*<<< orphan*/  strcasecmp (char const*,scalar_t__) ; 

__attribute__((used)) static const struct query_cmd *find_query(const char *name)
{
	const struct query_cmd *q;

	for (q = query_cmds; q->name; q++)
		if (!strcasecmp(name, q->name) ||
		    (q->alias && !strcasecmp(name, q->alias)))
			return q;

	return NULL;
}