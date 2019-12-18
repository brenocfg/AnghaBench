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
typedef  int uint32_t ;
struct codec_softc {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_RGADW ; 
 int /*<<< orphan*/  CODEC_RGDATA ; 
 int READ4 (struct codec_softc*,int /*<<< orphan*/ ) ; 
 int RGADW_RGADDR_S ; 
 int /*<<< orphan*/  WRITE4 (struct codec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
codec_read(struct codec_softc *sc, uint32_t reg)
{
	uint32_t tmp;

	clk_enable(sc->clk);

	tmp = (reg << RGADW_RGADDR_S);
	WRITE4(sc, CODEC_RGADW, tmp);

	tmp = READ4(sc, CODEC_RGDATA);

	clk_disable(sc->clk);

	return (tmp);
}