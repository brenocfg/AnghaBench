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
struct rt2560_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2560_CSR14 ; 
 int RT2560_ENABLE_TSF ; 
 int RT2560_ENABLE_TSF_SYNC (int) ; 

__attribute__((used)) static void
rt2560_enable_tsf(struct rt2560_softc *sc)
{
	RAL_WRITE(sc, RT2560_CSR14, 0);
	RAL_WRITE(sc, RT2560_CSR14,
	    RT2560_ENABLE_TSF_SYNC(2) | RT2560_ENABLE_TSF);
}