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
struct usb_ether {int /*<<< orphan*/  ue_eaddr; } ;
struct cue_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cue_getmac (struct cue_softc*,int /*<<< orphan*/ ) ; 
 struct cue_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
cue_attach_post(struct usb_ether *ue)
{
	struct cue_softc *sc = uether_getsc(ue);

	cue_getmac(sc, ue->ue_eaddr);
}