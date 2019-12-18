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
struct query_state {scalar_t__ uid; scalar_t__ euid; scalar_t__ gid; scalar_t__ egid; } ;

/* Variables and functions */

int
check_query_eids(struct query_state *qstate)
{

	return ((qstate->uid != qstate->euid) || (qstate->gid != qstate->egid) ? -1 : 0);
}