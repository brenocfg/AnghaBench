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
 int /*<<< orphan*/  hn_nvs_disconn_chim (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_nvs_disconn_rxbuf (struct hn_softc*) ; 

void
hn_nvs_detach(struct hn_softc *sc)
{

	/* NOTE: there are no requests to stop the NVS. */
	hn_nvs_disconn_rxbuf(sc);
	hn_nvs_disconn_chim(sc);
}