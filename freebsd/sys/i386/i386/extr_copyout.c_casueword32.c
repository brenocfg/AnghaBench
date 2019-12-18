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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  void* uint32_t ;
struct casueword_arg0 {int res; void* oldval; void* newval; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  casueword_slow0 ; 
 int cp_slow0 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct casueword_arg0*) ; 

int
casueword32(volatile uint32_t *base, uint32_t oldval, uint32_t *oldvalp,
    uint32_t newval)
{
	struct casueword_arg0 ca;
	int res;

	ca.oldval = oldval;
	ca.newval = newval;
	res = cp_slow0((vm_offset_t)base, sizeof(int32_t), true,
	    casueword_slow0, &ca);
	if (res == 0) {
		*oldvalp = ca.oldval;
		return (ca.res);
	}
	return (-1);
}