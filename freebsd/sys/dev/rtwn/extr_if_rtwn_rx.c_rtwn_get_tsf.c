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
typedef  int uint64_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int rtwn_get_tsf_high (struct rtwn_softc*,int) ; 
 scalar_t__ rtwn_get_tsf_low (struct rtwn_softc*,int) ; 

__attribute__((used)) static void
rtwn_get_tsf(struct rtwn_softc *sc, uint64_t *buf, int id)
{
	/* NB: we cannot read it at once. */
	*buf = rtwn_get_tsf_high(sc, id);
	*buf <<= 32;
	*buf += rtwn_get_tsf_low(sc, id);
}