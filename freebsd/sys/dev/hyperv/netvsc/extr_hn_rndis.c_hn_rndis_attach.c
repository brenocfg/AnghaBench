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
struct hn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hn_rndis_conf_offload (struct hn_softc*,int) ; 
 int hn_rndis_init (struct hn_softc*) ; 

int
hn_rndis_attach(struct hn_softc *sc, int mtu, int *init_done)
{
	int error;

	*init_done = 0;

	/*
	 * Initialize RNDIS.
	 */
	error = hn_rndis_init(sc);
	if (error)
		return (error);
	*init_done = 1;

	/*
	 * Configure NDIS offload settings.
	 */
	hn_rndis_conf_offload(sc, mtu);
	return (0);
}