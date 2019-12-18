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
struct socket {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;
struct ha_softc {scalar_t__ ha_listen; scalar_t__ ha_connect; struct socket* ha_so; scalar_t__ ha_receiving; int /*<<< orphan*/ * ha_sending; int /*<<< orphan*/  ha_sendq; scalar_t__ ha_connected; scalar_t__ ha_disconnect; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HA_CHAN_MAX ; 
 int /*<<< orphan*/  CTL_HA_EVT_LINK_CHANGE ; 
 int /*<<< orphan*/  CTL_HA_LINK_OFFLINE ; 
 int /*<<< orphan*/  CTL_HA_LINK_UNKNOWN ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_MTX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  SO_SND ; 
 int /*<<< orphan*/  ctl_ha_evt (struct ha_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 int /*<<< orphan*/  soupcall_clear (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
ctl_ha_close(struct ha_softc *softc)
{
	struct socket *so = softc->ha_so;
	int report = 0;

	if (softc->ha_connected || softc->ha_disconnect) {
		softc->ha_connected = 0;
		mbufq_drain(&softc->ha_sendq);
		m_freem(softc->ha_sending);
		softc->ha_sending = NULL;
		report = 1;
	}
	if (so) {
		SOCKBUF_LOCK(&so->so_rcv);
		soupcall_clear(so, SO_RCV);
		while (softc->ha_receiving) {
			wakeup(&softc->ha_receiving);
			msleep(&softc->ha_receiving, SOCKBUF_MTX(&so->so_rcv),
			    0, "ha_rx exit", 0);
		}
		SOCKBUF_UNLOCK(&so->so_rcv);
		SOCKBUF_LOCK(&so->so_snd);
		soupcall_clear(so, SO_SND);
		SOCKBUF_UNLOCK(&so->so_snd);
		softc->ha_so = NULL;
		if (softc->ha_connect)
			pause("reconnect", hz / 2);
		soclose(so);
	}
	if (report) {
		ctl_ha_evt(softc, CTL_HA_CHAN_MAX, CTL_HA_EVT_LINK_CHANGE,
		    (softc->ha_connect || softc->ha_listen) ?
		    CTL_HA_LINK_UNKNOWN : CTL_HA_LINK_OFFLINE);
	}
}