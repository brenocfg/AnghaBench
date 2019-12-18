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

/* Variables and functions */
 int /*<<< orphan*/  PMRN_PMC0 ; 
 int /*<<< orphan*/  PMRN_PMC1 ; 
 int /*<<< orphan*/  PMRN_PMC2 ; 
 int /*<<< orphan*/  PMRN_PMC3 ; 
 int /*<<< orphan*/  PMRN_PMC4 ; 
 int /*<<< orphan*/  PMRN_PMC5 ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void ctr_write(unsigned int i, unsigned int val)
{
	switch(i) {
		case 0:
			mtpmr(PMRN_PMC0, val);
			break;
		case 1:
			mtpmr(PMRN_PMC1, val);
			break;
		case 2:
			mtpmr(PMRN_PMC2, val);
			break;
		case 3:
			mtpmr(PMRN_PMC3, val);
			break;
		case 4:
			mtpmr(PMRN_PMC4, val);
			break;
		case 5:
			mtpmr(PMRN_PMC5, val);
			break;
		default:
			break;
	}
}