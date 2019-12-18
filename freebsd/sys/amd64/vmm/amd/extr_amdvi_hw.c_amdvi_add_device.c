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
typedef  int /*<<< orphan*/  uint16_t ;
struct amdvi_domain {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int RID2PCI_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdvi_inv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdvi_set_dte (struct amdvi_domain*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void
amdvi_add_device(void *arg, uint16_t devid)
{
	struct amdvi_domain *domain;

	domain = (struct amdvi_domain *)arg;
	KASSERT(domain != NULL, ("domain is NULL"));
#ifdef AMDVI_DEBUG_CMD
	printf("Assigning device(%d.%d.%d) to domain:%d\n",
	    RID2PCI_STR(devid), domain->id);
#endif
	amdvi_set_dte(domain, devid, true);
	amdvi_inv_device(devid);
}