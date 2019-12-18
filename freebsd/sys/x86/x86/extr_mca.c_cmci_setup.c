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
struct cmc_state {int dummy; } ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  M_MCA ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hw_mca ; 
 void** cmc_state ; 
 int /*<<< orphan*/  cmc_throttle ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mca_banks ; 
 int mp_maxid ; 
 int /*<<< orphan*/  sysctl_positive_int ; 

__attribute__((used)) static void
cmci_setup(void)
{
	int i;

	cmc_state = malloc((mp_maxid + 1) * sizeof(struct cmc_state *), M_MCA,
	    M_WAITOK);
	for (i = 0; i <= mp_maxid; i++)
		cmc_state[i] = malloc(sizeof(struct cmc_state) * mca_banks,
		    M_MCA, M_WAITOK | M_ZERO);
	SYSCTL_ADD_PROC(NULL, SYSCTL_STATIC_CHILDREN(_hw_mca), OID_AUTO,
	    "cmc_throttle", CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_MPSAFE,
	    &cmc_throttle, 0, sysctl_positive_int, "I",
	    "Interval in seconds to throttle corrected MC interrupts");
}