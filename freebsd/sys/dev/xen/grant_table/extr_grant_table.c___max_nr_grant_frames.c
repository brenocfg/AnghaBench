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
struct gnttab_query_size {scalar_t__ status; unsigned int max_nr_frames; int /*<<< orphan*/  dom; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 scalar_t__ GNTST_okay ; 
 int /*<<< orphan*/  GNTTABOP_query_size ; 
 int HYPERVISOR_grant_table_op (int /*<<< orphan*/ ,struct gnttab_query_size*,int) ; 

__attribute__((used)) static unsigned int
__max_nr_grant_frames(void)
{
	struct gnttab_query_size query;
	int rc;

	query.dom = DOMID_SELF;

	rc = HYPERVISOR_grant_table_op(GNTTABOP_query_size, &query, 1);
	if ((rc < 0) || (query.status != GNTST_okay))
		return (4); /* Legacy max supported number of frames */

	return (query.max_nr_frames);
}