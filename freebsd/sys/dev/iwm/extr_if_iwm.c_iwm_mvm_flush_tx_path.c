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
typedef  int /*<<< orphan*/  uint32_t ;
struct iwm_tx_path_flush_cmd {int /*<<< orphan*/  flush_ctl; int /*<<< orphan*/  queues_ctl; } ;
struct iwm_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  flush_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_DUMP_TX_FIFO_FLUSH ; 
 int /*<<< orphan*/  IWM_TXPATH_FLUSH ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int iwm_mvm_send_cmd_pdu (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwm_tx_path_flush_cmd*) ; 

int
iwm_mvm_flush_tx_path(struct iwm_softc *sc, uint32_t tfd_msk, uint32_t flags)
{
	int ret;
	struct iwm_tx_path_flush_cmd flush_cmd = {
		.queues_ctl = htole32(tfd_msk),
		.flush_ctl = htole16(IWM_DUMP_TX_FIFO_FLUSH),
	};

	ret = iwm_mvm_send_cmd_pdu(sc, IWM_TXPATH_FLUSH, flags,
	    sizeof(flush_cmd), &flush_cmd);
	if (ret)
                device_printf(sc->sc_dev,
		    "Flushing tx queue failed: %d\n", ret);
	return ret;
}