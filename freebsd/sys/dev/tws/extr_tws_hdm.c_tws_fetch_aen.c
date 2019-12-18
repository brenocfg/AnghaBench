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
struct tws_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tws_send_scsi_cmd (struct tws_softc*,int) ; 

void
tws_fetch_aen(void *arg)
{
    struct tws_softc *sc = (struct tws_softc *)arg;
    int error = 0;

    TWS_TRACE_DEBUG(sc, "entry", 0, 0);

    if ((error = tws_send_scsi_cmd(sc, 0x03 /* REQUEST_SENSE */))) {
        TWS_TRACE_DEBUG(sc, "aen fetch send in progress", 0, 0);
    }
}