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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int RTWN_RX_DATA ; 

int
r92c_classify_intr(struct rtwn_softc *sc, void *buf, int len)
{
	/* NB: reports are fetched from C2H_MSG register. */
	return (RTWN_RX_DATA);
}