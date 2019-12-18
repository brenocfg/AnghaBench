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
struct sa_handle {int dummy; } ;
struct query_params {int dummy; } ;
struct query_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SA_ATTR_SERVICERECORD ; 
 int /*<<< orphan*/  dump_service_record ; 
 int get_and_dump_all_records (struct sa_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct query_params*) ; 

__attribute__((used)) static int query_service_records(const struct query_cmd *q, struct sa_handle * h,
				 struct query_params *p, int argc, char *argv[])
{
	return get_and_dump_all_records(h, IB_SA_ATTR_SERVICERECORD,
					dump_service_record, p);
}