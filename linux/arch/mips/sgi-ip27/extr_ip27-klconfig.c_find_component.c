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
typedef  int /*<<< orphan*/  lboard_t ;
typedef  int /*<<< orphan*/  klinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/ * KLCF_COMP (int /*<<< orphan*/ *,int) ; 
 unsigned char KLCF_COMP_TYPE (int /*<<< orphan*/ *) ; 
 int KLCF_NUM_COMPS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ *) ; 

klinfo_t *find_component(lboard_t *brd, klinfo_t *kli, unsigned char struct_type)
{
	int index, j;

	if (kli == (klinfo_t *)NULL) {
		index = 0;
	} else {
		for (j = 0; j < KLCF_NUM_COMPS(brd); j++)
			if (kli == KLCF_COMP(brd, j))
				break;
		index = j;
		if (index == KLCF_NUM_COMPS(brd)) {
			printk("find_component: Bad pointer: 0x%p\n", kli);
			return (klinfo_t *)NULL;
		}
		index++;		/* next component */
	}

	for (; index < KLCF_NUM_COMPS(brd); index++) {
		kli = KLCF_COMP(brd, index);
		if (KLCF_COMP_TYPE(kli) == struct_type)
			return kli;
	}

	/* Didn't find it. */
	return (klinfo_t *)NULL;
}