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
typedef  int u_short ;
struct amdpm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDPM_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDPM_LOCK_ASSERT (struct amdpm_softc*) ; 
 int AMDPM_SMBINW (struct amdpm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDSMB_GLOBAL_STATUS ; 
 int AMDSMB_GS_HST_STS ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
amdpm_idle(struct amdpm_softc *sc)
{
	u_short sts;

	AMDPM_LOCK_ASSERT(sc);
	sts = AMDPM_SMBINW(sc, AMDSMB_GLOBAL_STATUS);

	AMDPM_DEBUG(printf("amdpm: busy? STS=0x%x\n", sts));

	return (~(sts & AMDSMB_GS_HST_STS));
}