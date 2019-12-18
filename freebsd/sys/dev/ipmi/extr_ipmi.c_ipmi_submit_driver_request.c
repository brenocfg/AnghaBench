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
struct ipmi_softc {int (* ipmi_driver_request ) (struct ipmi_softc*,struct ipmi_request*,int) ;} ;
struct ipmi_request {int dummy; } ;

/* Variables and functions */
 int stub1 (struct ipmi_softc*,struct ipmi_request*,int) ; 

int
ipmi_submit_driver_request(struct ipmi_softc *sc, struct ipmi_request *req,
    int timo)
{

	return (sc->ipmi_driver_request(sc, req, timo));
}