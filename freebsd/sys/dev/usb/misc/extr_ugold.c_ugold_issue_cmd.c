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
typedef  int /*<<< orphan*/  uint8_t ;
struct ugold_softc {int /*<<< orphan*/  sc_report_id; int /*<<< orphan*/ * sc_iface_index; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UHID_OUTPUT_REPORT ; 
 int usbd_req_set_report (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ugold_issue_cmd(struct ugold_softc *sc, uint8_t *cmd, int len)
{
	return (usbd_req_set_report(sc->sc_udev, &sc->sc_mtx, cmd, len,
	    sc->sc_iface_index[1], UHID_OUTPUT_REPORT, sc->sc_report_id));
}