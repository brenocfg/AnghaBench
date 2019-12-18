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
struct ifbrparam {int /*<<< orphan*/  ifbrp_txhc; } ;
struct bridge_softc {int /*<<< orphan*/  sc_stp; } ;

/* Variables and functions */
 int bstp_set_holdcount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_ioctl_stxhc(struct bridge_softc *sc, void *arg)
{
	struct ifbrparam *param = arg;

	return (bstp_set_holdcount(&sc->sc_stp, param->ifbrp_txhc));
}