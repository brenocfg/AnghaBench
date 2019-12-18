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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AR_DCHNTIME (int) ; 
 int /*<<< orphan*/  AR_DLCL_IFS (int) ; 
 int /*<<< orphan*/  AR_DMISC (int) ; 
 int /*<<< orphan*/  AR_DQCUMASK (int) ; 
 int /*<<< orphan*/  AR_DRETRY_LIMIT (int) ; 
 int OS_REG_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ah ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static void
ath_hal_dumpdcu(FILE *fd, int what)
{
	int i;

	/* DCU registers */
	for (i = 0; i < 10; i++)
		fprintf(fd, "D[%u] MASK %08x IFS %08x RTRY %08x CHNT %08x MISC %06x\n"
			, i
			, OS_REG_READ(ah, AR_DQCUMASK(i))
			, OS_REG_READ(ah, AR_DLCL_IFS(i))
			, OS_REG_READ(ah, AR_DRETRY_LIMIT(i))
			, OS_REG_READ(ah, AR_DCHNTIME(i))
			, OS_REG_READ(ah, AR_DMISC(i))
		);
}