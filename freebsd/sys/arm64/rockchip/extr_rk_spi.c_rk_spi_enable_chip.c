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
struct rk_spi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK_SPI_ENR ; 
 int /*<<< orphan*/  RK_SPI_WRITE_4 (struct rk_spi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rk_spi_enable_chip(struct rk_spi_softc *sc, int enable)
{

	RK_SPI_WRITE_4(sc, RK_SPI_ENR, enable ? 1 : 0);
}