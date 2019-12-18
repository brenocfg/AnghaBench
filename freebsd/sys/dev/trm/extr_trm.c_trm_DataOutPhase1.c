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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  PSRB ;
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 int /*<<< orphan*/  XFERDATAOUT ; 
 int /*<<< orphan*/  trm_DataIO_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trm_DataOutPhase1(PACB pACB, PSRB pSRB, u_int16_t *pscsi_status)
{
	u_int16_t	ioDir;
	/*
	 * do prepare befor transfer when data out phase
	 */

	ioDir = XFERDATAOUT;
	trm_DataIO_transfer(pACB, pSRB, ioDir);
}