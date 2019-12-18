#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ib_srq_attr {int dummy; } ;
struct ib_srq {TYPE_1__* device; } ;
struct TYPE_2__ {int (* query_srq ) (struct ib_srq*,struct ib_srq_attr*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct ib_srq*,struct ib_srq_attr*) ; 

int ib_query_srq(struct ib_srq *srq,
		 struct ib_srq_attr *srq_attr)
{
	return srq->device->query_srq ?
		srq->device->query_srq(srq, srq_attr) : -ENOSYS;
}