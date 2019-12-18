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
struct rt2661_softc {int dummy; } ;

/* Variables and functions */
 int RAL_READ (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2661_TSF_MODE (int) ; 
 int RT2661_TSF_TICKING ; 
 int /*<<< orphan*/  RT2661_TXRX_CSR9 ; 

__attribute__((used)) static void
rt2661_enable_tsf(struct rt2661_softc *sc)
{
	RAL_WRITE(sc, RT2661_TXRX_CSR9, 
	      (RAL_READ(sc, RT2661_TXRX_CSR9) & 0xff000000)
	    | RT2661_TSF_TICKING | RT2661_TSF_MODE(2));
}