#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sa_query_result {int /*<<< orphan*/  p_result_madw; } ;
struct sa_handle {int dummy; } ;
typedef  int /*<<< orphan*/  pr ;
typedef  int /*<<< orphan*/  ibmad_gid_t ;
struct TYPE_5__ {int /*<<< orphan*/  dgid; int /*<<< orphan*/  dlid; int /*<<< orphan*/  slid; } ;
typedef  TYPE_1__ ib_path_rec_t ;
typedef  int /*<<< orphan*/  ib_net64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_AND_SET_VAL (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DLID ; 
 int /*<<< orphan*/  IB_SA_ATTR_PATHRECORD ; 
 int /*<<< orphan*/  PR ; 
 int /*<<< orphan*/  SLID ; 
 int get_any_records (struct sa_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,struct sa_query_result*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sa_free_result_mad (struct sa_query_result*) ; 
 TYPE_1__* sa_get_query_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sm_pr_query(struct sa_handle * h, ibmad_gid_t *gid, int srclid, int destlid) {

	ib_path_rec_t pr;
	ib_net64_t comp_mask = 0;
	struct sa_query_result result;
	int ret;
	ib_path_rec_t *p_pr;

	memset(&pr, 0, sizeof(pr));
	CHECK_AND_SET_VAL(srclid, 16, 0, pr.slid, PR, SLID);
	CHECK_AND_SET_VAL(destlid, 16, 0, pr.dlid, PR, DLID);

	ret = get_any_records(h, IB_SA_ATTR_PATHRECORD, 0, comp_mask, &pr, sizeof(pr), &result);
	if (ret)
		return ret;

	p_pr = sa_get_query_rec(result.p_result_madw, 0);
	memcpy(gid, &p_pr->dgid, 16);
	sa_free_result_mad(&result);
	return ret;
}