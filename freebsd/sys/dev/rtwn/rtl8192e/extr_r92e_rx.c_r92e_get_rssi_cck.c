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
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 scalar_t__ r88e_get_rssi_cck (struct rtwn_softc*,void*) ; 

int8_t
r92e_get_rssi_cck(struct rtwn_softc *sc, void *physt)
{

	return (10 + r88e_get_rssi_cck(sc, physt));
}