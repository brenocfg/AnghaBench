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
struct vtnet_softc {int dummy; } ;

/* Variables and functions */
 int vtnet_init_rx_queues (struct vtnet_softc*) ; 
 int vtnet_init_tx_queues (struct vtnet_softc*) ; 

__attribute__((used)) static int
vtnet_init_rxtx_queues(struct vtnet_softc *sc)
{
	int error;

	error = vtnet_init_rx_queues(sc);
	if (error)
		return (error);

	error = vtnet_init_tx_queues(sc);
	if (error)
		return (error);

	return (0);
}