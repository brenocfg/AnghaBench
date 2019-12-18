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
struct TYPE_2__ {int max_uvolt; int min_uvolt; } ;
struct regnode {TYPE_1__ std_param; } ;

/* Variables and functions */
 int ERANGE ; 

__attribute__((used)) static int
regnode_method_set_voltage(struct regnode *regnode, int min_uvolt, int max_uvolt,
    int *udelay)
{

	if ((min_uvolt > regnode->std_param.max_uvolt) ||
	    (max_uvolt < regnode->std_param.min_uvolt))
		return (ERANGE);
	*udelay = 0;
	return (0);
}