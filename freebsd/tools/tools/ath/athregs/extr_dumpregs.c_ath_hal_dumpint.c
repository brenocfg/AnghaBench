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
 int /*<<< orphan*/  AR_IMR ; 
 int /*<<< orphan*/  AR_IMR_S0 ; 
 int /*<<< orphan*/  AR_IMR_S1 ; 
 int /*<<< orphan*/  AR_IMR_S2 ; 
 int /*<<< orphan*/  AR_IMR_S3 ; 
 int /*<<< orphan*/  AR_IMR_S4 ; 
 int /*<<< orphan*/  AR_ISR ; 
 int /*<<< orphan*/  AR_ISR_S0 ; 
 int /*<<< orphan*/  AR_ISR_S1 ; 
 int /*<<< orphan*/  AR_ISR_S2 ; 
 int /*<<< orphan*/  AR_ISR_S3 ; 
 int /*<<< orphan*/  AR_ISR_S4 ; 
 int OS_REG_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ah ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static void
ath_hal_dumpint(FILE *fd, int what)
{
	int i;

	/* Interrupt registers */
	fprintf(fd, "IMR: %08x S0 %08x S1 %08x S2 %08x S3 %08x S4 %08x\n"
		, OS_REG_READ(ah, AR_IMR)
		, OS_REG_READ(ah, AR_IMR_S0)
		, OS_REG_READ(ah, AR_IMR_S1)
		, OS_REG_READ(ah, AR_IMR_S2)
		, OS_REG_READ(ah, AR_IMR_S3)
		, OS_REG_READ(ah, AR_IMR_S4)
	);
	fprintf(fd, "ISR: %08x S0 %08x S1 %08x S2 %08x S3 %08x S4 %08x\n"
		, OS_REG_READ(ah, AR_ISR)
		, OS_REG_READ(ah, AR_ISR_S0)
		, OS_REG_READ(ah, AR_ISR_S1)
		, OS_REG_READ(ah, AR_ISR_S2)
		, OS_REG_READ(ah, AR_ISR_S3)
		, OS_REG_READ(ah, AR_ISR_S4)
	);
}