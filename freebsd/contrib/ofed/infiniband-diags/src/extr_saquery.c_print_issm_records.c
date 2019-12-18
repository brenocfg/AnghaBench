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
struct sa_query_result {int dummy; } ;
struct sa_handle {int dummy; } ;
struct query_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PORT_CAP_IS_SM ; 
 int /*<<< orphan*/  IB_PORT_CAP_SM_DISAB ; 
 int /*<<< orphan*/  dump_portinfo_record ; 
 int /*<<< orphan*/  dump_results (struct sa_query_result*,int /*<<< orphan*/ ,struct query_params*) ; 
 int get_issm_records (struct sa_handle*,int /*<<< orphan*/ ,struct sa_query_result*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sa_free_result_mad (struct sa_query_result*) ; 

__attribute__((used)) static int print_issm_records(struct sa_handle * h, struct query_params *p)
{
	struct sa_query_result result;
	int ret = 0;

	/* First, get IsSM records */
	ret = get_issm_records(h, IB_PORT_CAP_IS_SM, &result);
	if (ret != 0)
		return (ret);

	printf("IsSM ports\n");
	dump_results(&result, dump_portinfo_record, p);
	sa_free_result_mad(&result);

	/* Now, get IsSMdisabled records */
	ret = get_issm_records(h, IB_PORT_CAP_SM_DISAB, &result);
	if (ret != 0)
		return (ret);

	printf("\nIsSMdisabled ports\n");
	dump_results(&result, dump_portinfo_record, p);
	sa_free_result_mad(&result);

	return (ret);
}