#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tm {int dummy; } ;
struct TYPE_3__ {scalar_t__ hi; int /*<<< orphan*/  lo; } ;
typedef  TYPE_1__ ntpcal_split ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ ntpcal_daysec_to_tm (struct tm*,int /*<<< orphan*/ ) ; 
 int ntpcal_rd_to_tm (struct tm*,scalar_t__) ; 

int
ntpcal_daysplit_to_tm(
	struct tm	   *utm,
	const ntpcal_split *ds ,
	int32_t		    dof
	)
{
	dof += ntpcal_daysec_to_tm(utm, ds->lo);

	return ntpcal_rd_to_tm(utm, ds->hi + dof);
}