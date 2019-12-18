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
struct iwi_softc {int sc_linkqual_valid; int /*<<< orphan*/  sc_linkqual; } ;
struct iwi_notif_link_quality {int dummy; } ;
struct iwi_notif {int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iwi_notif_link_quality*,int) ; 

__attribute__((used)) static void
iwi_notif_link_quality(struct iwi_softc *sc, struct iwi_notif *notif)
{
	struct iwi_notif_link_quality *lq;
	int len;

	len = le16toh(notif->len);

	DPRINTFN(5, ("Notification (%u) - len=%d, sizeof=%zu\n",
	    notif->type,
	    len,
	    sizeof(struct iwi_notif_link_quality)
	    ));

	/* enforce length */
	if (len != sizeof(struct iwi_notif_link_quality)) {
		DPRINTFN(5, ("Notification: (%u) too short (%d)\n",
		    notif->type,
		    len));
		return;
	}

	lq = (struct iwi_notif_link_quality *)(notif + 1);
	memcpy(&sc->sc_linkqual, lq, sizeof(sc->sc_linkqual));
	sc->sc_linkqual_valid = 1;
}