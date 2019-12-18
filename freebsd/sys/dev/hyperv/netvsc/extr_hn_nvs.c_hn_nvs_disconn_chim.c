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
struct hn_softc {int hn_flags; scalar_t__ hn_chim_gpadl; scalar_t__ hn_chim_bmap_cnt; int /*<<< orphan*/ * hn_chim_bmap; int /*<<< orphan*/  hn_ifp; int /*<<< orphan*/  hn_prichan; } ;
struct hn_nvs_chim_disconn {int /*<<< orphan*/  nvs_sig; int /*<<< orphan*/  nvs_type; } ;
typedef  int /*<<< orphan*/  disconn ;

/* Variables and functions */
 int HN_FLAG_CHIM_CONNECTED ; 
 int HN_FLAG_CHIM_REF ; 
 int /*<<< orphan*/  HN_NVS_CHIM_SIG ; 
 int /*<<< orphan*/  HN_NVS_TYPE_CHIM_DISCONN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ VMBUS_VERSION_WIN10 ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hn_nvs_req_send (struct hn_softc*,struct hn_nvs_chim_disconn*,int) ; 
 int hz ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct hn_nvs_chim_disconn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int vmbus_chan_gpadl_disconnect (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vmbus_chan_is_revoked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_chan_tx_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ vmbus_current_version ; 

__attribute__((used)) static void
hn_nvs_disconn_chim(struct hn_softc *sc)
{
	int error;

	if (sc->hn_flags & HN_FLAG_CHIM_CONNECTED) {
		struct hn_nvs_chim_disconn disconn;

		/*
		 * Disconnect chimney sending buffer from NVS.
		 */
		memset(&disconn, 0, sizeof(disconn));
		disconn.nvs_type = HN_NVS_TYPE_CHIM_DISCONN;
		disconn.nvs_sig = HN_NVS_CHIM_SIG;

		/* NOTE: No response. */
		error = hn_nvs_req_send(sc, &disconn, sizeof(disconn));
		if (error) {
			if_printf(sc->hn_ifp,
			    "send nvs chim disconn failed: %d\n", error);
			/*
			 * Fine for a revoked channel, since the hypervisor
			 * does not drain TX bufring for a revoked channel.
			 */
			if (!vmbus_chan_is_revoked(sc->hn_prichan))
				sc->hn_flags |= HN_FLAG_CHIM_REF;
		}
		sc->hn_flags &= ~HN_FLAG_CHIM_CONNECTED;

		/*
		 * Wait for the hypervisor to receive this NVS request.
		 *
		 * NOTE:
		 * The TX bufring will not be drained by the hypervisor,
		 * if the primary channel is revoked.
		 */
		while (!vmbus_chan_tx_empty(sc->hn_prichan) &&
		    !vmbus_chan_is_revoked(sc->hn_prichan))
			pause("waittx", 1);
		/*
		 * Linger long enough for NVS to disconnect chimney
		 * sending buffer.
		 */
		pause("lingtx", (200 * hz) / 1000);
	}

	if (vmbus_current_version < VMBUS_VERSION_WIN10 && sc->hn_chim_gpadl != 0) {
		/*
		 * Disconnect chimney sending buffer from primary channel.
		 */
		error = vmbus_chan_gpadl_disconnect(sc->hn_prichan,
		    sc->hn_chim_gpadl);
		if (error) {
			if_printf(sc->hn_ifp,
			    "chim gpadl disconn failed: %d\n", error);
			sc->hn_flags |= HN_FLAG_CHIM_REF;
		}
		sc->hn_chim_gpadl = 0;
	}

	if (sc->hn_chim_bmap != NULL) {
		free(sc->hn_chim_bmap, M_DEVBUF);
		sc->hn_chim_bmap = NULL;
		sc->hn_chim_bmap_cnt = 0;
	}
}