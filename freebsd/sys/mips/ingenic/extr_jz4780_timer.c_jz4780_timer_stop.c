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
struct jz4780_timer_softc {int dummy; } ;
struct eventtimer {scalar_t__ et_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct jz4780_timer_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_TC_TECR ; 
 int /*<<< orphan*/  TESR_TCST5 ; 

__attribute__((used)) static int
jz4780_timer_stop(struct eventtimer *et)
{
	struct jz4780_timer_softc *sc =
	    (struct jz4780_timer_softc *)et->et_priv;

	CSR_WRITE_4(sc, JZ_TC_TECR, TESR_TCST5);
	return (0);
}