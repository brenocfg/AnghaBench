#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sa_query_result {int dummy; } ;
struct sa_handle {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  capability_mask; } ;
struct TYPE_6__ {TYPE_1__ port_info; } ;
typedef  TYPE_2__ ib_portinfo_record_t ;
typedef  int /*<<< orphan*/  ib_net32_t ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PIR_COMPMASK_CAPMASK ; 
 int /*<<< orphan*/  IB_SA_ATTR_PORTINFORECORD ; 
 int get_any_records (struct sa_handle*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*,int,struct sa_query_result*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_issm_records(struct sa_handle * h, ib_net32_t capability_mask,
			    struct sa_query_result *result)
{
	ib_portinfo_record_t attr;

	memset(&attr, 0, sizeof(attr));
	attr.port_info.capability_mask = capability_mask;

	return get_any_records(h, IB_SA_ATTR_PORTINFORECORD, 1 << 31,
			       IB_PIR_COMPMASK_CAPMASK, &attr, sizeof(attr), result);
}