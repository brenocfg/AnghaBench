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
struct aml8726_sdxc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_SDXC_SOFT_RESET ; 
 int /*<<< orphan*/  AML_SDXC_SOFT_RESET_REG ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static void
aml8726_sdxc_soft_reset(struct aml8726_sdxc_softc *sc)
{

	CSR_WRITE_4(sc, AML_SDXC_SOFT_RESET_REG, AML_SDXC_SOFT_RESET);
	CSR_BARRIER(sc, AML_SDXC_SOFT_RESET_REG);
	DELAY(5);
}