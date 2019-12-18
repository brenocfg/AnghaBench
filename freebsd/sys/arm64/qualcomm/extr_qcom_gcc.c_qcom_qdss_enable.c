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
struct qcom_gcc_softc {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHB_CBCR_CLK_ENABLE ; 
 int /*<<< orphan*/  DAP_CBCR_CLK_ENABLE ; 
 int /*<<< orphan*/  ETR_USB_CBCR_CLK_ENABLE ; 
 int /*<<< orphan*/  GCC_QDSS_BCR ; 
 int /*<<< orphan*/  GCC_QDSS_BCR_BLK_ARES ; 
 int /*<<< orphan*/  GCC_QDSS_CFG_AHB_CBCR ; 
 int /*<<< orphan*/  GCC_QDSS_DAP_CBCR ; 
 int /*<<< orphan*/  GCC_QDSS_ETR_USB_CBCR ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qcom_qdss_enable(struct qcom_gcc_softc *sc)
{

	/* Put QDSS block to reset */
	bus_write_4(sc->res, GCC_QDSS_BCR, GCC_QDSS_BCR_BLK_ARES);

	/* Enable AHB clock branch */
	bus_write_4(sc->res, GCC_QDSS_CFG_AHB_CBCR, AHB_CBCR_CLK_ENABLE);

	/* Enable DAP clock branch */
	bus_write_4(sc->res, GCC_QDSS_DAP_CBCR, DAP_CBCR_CLK_ENABLE);

	/* Enable ETR USB clock branch */
	bus_write_4(sc->res, GCC_QDSS_ETR_USB_CBCR, ETR_USB_CBCR_CLK_ENABLE);

	/* Out of reset */
	bus_write_4(sc->res, GCC_QDSS_BCR, 0);
}