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
 int /*<<< orphan*/  AR_QCBRCFG (int) ; 
 int /*<<< orphan*/  AR_QMISC (int) ; 
 int /*<<< orphan*/  AR_QRDYTIMECFG (int) ; 
 int /*<<< orphan*/  AR_QSTS (int) ; 
 int /*<<< orphan*/  AR_QTXDP (int) ; 
 int /*<<< orphan*/  AR_Q_ONESHOTARM_CC ; 
 int /*<<< orphan*/  AR_Q_ONESHOTARM_SC ; 
 int /*<<< orphan*/  AR_Q_RDYTIMESHDN ; 
 int /*<<< orphan*/  AR_Q_TXD ; 
 int /*<<< orphan*/  AR_Q_TXE ; 
 int OS_REG_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ah ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
ath_hal_dumpqcu(FILE *fd, int what)
{
	int i;

	/* QCU registers */
	fprintf(fd, "%-8s %08x  %-8s %08x  %-8s %08x\n"
		, "Q_TXE", OS_REG_READ(ah, AR_Q_TXE)
		, "Q_TXD", OS_REG_READ(ah, AR_Q_TXD)
		, "Q_RDYTIMSHD", OS_REG_READ(ah, AR_Q_RDYTIMESHDN)
	);
	fprintf(fd, "Q_ONESHOTARM_SC %08x  Q_ONESHOTARM_CC %08x\n"
		, OS_REG_READ(ah, AR_Q_ONESHOTARM_SC)
		, OS_REG_READ(ah, AR_Q_ONESHOTARM_CC)
	);
	for (i = 0; i < 10; i++)
		fprintf(fd, "Q[%u] TXDP %08x CBR %08x RDYT %08x MISC %08x STS %08x\n"
			, i
			, OS_REG_READ(ah, AR_QTXDP(i))
			, OS_REG_READ(ah, AR_QCBRCFG(i))
			, OS_REG_READ(ah, AR_QRDYTIMECFG(i))
			, OS_REG_READ(ah, AR_QMISC(i))
			, OS_REG_READ(ah, AR_QSTS(i))
		);
}