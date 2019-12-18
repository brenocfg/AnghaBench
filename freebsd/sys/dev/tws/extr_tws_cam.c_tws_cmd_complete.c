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
struct tws_request {int /*<<< orphan*/  timeout; struct tws_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_unmap_request (struct tws_softc*,struct tws_request*) ; 

void
tws_cmd_complete(struct tws_request *req)
{
    struct tws_softc *sc = req->sc;

    callout_stop(&req->timeout);
    tws_unmap_request(sc, req);
}