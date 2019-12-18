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
struct TYPE_2__ {scalar_t__ ddr_type; } ;
struct diffarg {int da_err; int* da_offp; TYPE_1__ da_ddr; } ;

/* Variables and functions */
 scalar_t__ DDR_NONE ; 
 int write_bytes (struct diffarg*) ; 

__attribute__((used)) static int
write_record(struct diffarg *da)
{

	if (da->da_ddr.ddr_type == DDR_NONE) {
		da->da_err = 0;
		return (0);
	}

	da->da_err = write_bytes(da);
	*da->da_offp += sizeof (da->da_ddr);
	return (da->da_err);
}