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
typedef  int u_char ;
struct alpm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPM_DEBUG (int /*<<< orphan*/ ) ; 
 int ALPM_SMBINB (struct alpm_softc*,int /*<<< orphan*/ ) ; 
 int IDL_STS ; 
 int /*<<< orphan*/  SMBSTS ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
alpm_idle(struct alpm_softc *sc)
{
	u_char sts;

	sts = ALPM_SMBINB(sc, SMBSTS);

	ALPM_DEBUG(printf("alpm: idle? STS=0x%x\n", sts));

	return (sts & IDL_STS);
}