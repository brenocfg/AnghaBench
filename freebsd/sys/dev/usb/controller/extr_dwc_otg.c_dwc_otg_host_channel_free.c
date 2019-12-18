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
typedef  scalar_t__ uint8_t ;
struct dwc_otg_td {scalar_t__ max_packet_count; } ;
struct dwc_otg_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc_otg_host_channel_free_sub (struct dwc_otg_softc*,struct dwc_otg_td*,scalar_t__) ; 

__attribute__((used)) static void
dwc_otg_host_channel_free(struct dwc_otg_softc *sc, struct dwc_otg_td *td)
{
	uint8_t x;
	for (x = 0; x != td->max_packet_count; x++)
		dwc_otg_host_channel_free_sub(sc, td, x);
}