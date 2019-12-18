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
struct ib_ah_attr {int dummy; } ;
struct ib_ah {TYPE_1__* device; } ;
struct TYPE_2__ {int (* query_ah ) (struct ib_ah*,struct ib_ah_attr*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct ib_ah*,struct ib_ah_attr*) ; 

int ib_query_ah(struct ib_ah *ah, struct ib_ah_attr *ah_attr)
{
	return ah->device->query_ah ?
		ah->device->query_ah(ah, ah_attr) :
		-ENOSYS;
}