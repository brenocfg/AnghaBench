#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sfxge_intr {scalar_t__ state; int n_alloc; } ;
struct sfxge_softc {int txq_count; scalar_t__ txq_dynamic_cksum_toggle_supported; int /*<<< orphan*/ * txqs_node; int /*<<< orphan*/  dev; int /*<<< orphan*/  tso_fw_assisted; struct sfxge_intr intr; int /*<<< orphan*/  enp; } ;
struct TYPE_3__ {int enc_features; int /*<<< orphan*/  enc_fw_assisted_tso_v2_enabled; int /*<<< orphan*/  enc_fw_assisted_tso_enabled; } ;
typedef  TYPE_1__ efx_nic_cfg_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int EFX_FEATURE_FW_ASSISTED_TSO ; 
 int EFX_FEATURE_FW_ASSISTED_TSO_V2 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int SFXGE_EVQ0_N_TXQ (struct sfxge_softc*) ; 
 int /*<<< orphan*/  SFXGE_FATSOV1 ; 
 int /*<<< orphan*/  SFXGE_FATSOV2 ; 
 scalar_t__ SFXGE_INTR_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_PARAM_TX_DPL_GET_MAX ; 
 int /*<<< orphan*/  SFXGE_PARAM_TX_DPL_GET_NON_TCP_MAX ; 
 int /*<<< orphan*/  SFXGE_PARAM_TX_DPL_PUT_MAX ; 
 int SFXGE_TXQ_IP_CKSUM ; 
 int SFXGE_TXQ_IP_TCP_UDP_CKSUM ; 
 int SFXGE_TXQ_NON_CKSUM ; 
 int /*<<< orphan*/ * SYSCTL_ADD_NODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 TYPE_1__* efx_nic_cfg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sfxge_tso_fw_assisted ; 
 scalar_t__ sfxge_tx_dpl_get_max ; 
 scalar_t__ sfxge_tx_dpl_get_non_tcp_max ; 
 scalar_t__ sfxge_tx_dpl_put_max ; 
 int /*<<< orphan*/  sfxge_tx_qfini (struct sfxge_softc*,int) ; 
 int sfxge_tx_qinit (struct sfxge_softc*,int,int,int) ; 
 int /*<<< orphan*/  sfxge_tx_stat_init (struct sfxge_softc*) ; 

int
sfxge_tx_init(struct sfxge_softc *sc)
{
	const efx_nic_cfg_t *encp = efx_nic_cfg_get(sc->enp);
	struct sfxge_intr *intr;
	int index;
	int rc;

	intr = &sc->intr;

	KASSERT(intr->state == SFXGE_INTR_INITIALIZED,
	    ("intr->state != SFXGE_INTR_INITIALIZED"));

	if (sfxge_tx_dpl_get_max <= 0) {
		log(LOG_ERR, "%s=%d must be greater than 0",
		    SFXGE_PARAM_TX_DPL_GET_MAX, sfxge_tx_dpl_get_max);
		rc = EINVAL;
		goto fail_tx_dpl_get_max;
	}
	if (sfxge_tx_dpl_get_non_tcp_max <= 0) {
		log(LOG_ERR, "%s=%d must be greater than 0",
		    SFXGE_PARAM_TX_DPL_GET_NON_TCP_MAX,
		    sfxge_tx_dpl_get_non_tcp_max);
		rc = EINVAL;
		goto fail_tx_dpl_get_non_tcp_max;
	}
	if (sfxge_tx_dpl_put_max < 0) {
		log(LOG_ERR, "%s=%d must be greater or equal to 0",
		    SFXGE_PARAM_TX_DPL_PUT_MAX, sfxge_tx_dpl_put_max);
		rc = EINVAL;
		goto fail_tx_dpl_put_max;
	}

	sc->txq_count = SFXGE_EVQ0_N_TXQ(sc) - 1 + sc->intr.n_alloc;

	sc->tso_fw_assisted = sfxge_tso_fw_assisted;
	if ((~encp->enc_features & EFX_FEATURE_FW_ASSISTED_TSO) ||
	    (!encp->enc_fw_assisted_tso_enabled))
		sc->tso_fw_assisted &= ~SFXGE_FATSOV1;
	if ((~encp->enc_features & EFX_FEATURE_FW_ASSISTED_TSO_V2) ||
	    (!encp->enc_fw_assisted_tso_v2_enabled))
		sc->tso_fw_assisted &= ~SFXGE_FATSOV2;

	sc->txqs_node = SYSCTL_ADD_NODE(
		device_get_sysctl_ctx(sc->dev),
		SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev)),
		OID_AUTO, "txq", CTLFLAG_RD, NULL, "Tx queues");
	if (sc->txqs_node == NULL) {
		rc = ENOMEM;
		goto fail_txq_node;
	}

	/* Initialize the transmit queues */
	if (sc->txq_dynamic_cksum_toggle_supported == B_FALSE) {
		if ((rc = sfxge_tx_qinit(sc, SFXGE_TXQ_NON_CKSUM,
		    SFXGE_TXQ_NON_CKSUM, 0)) != 0)
			goto fail;

		if ((rc = sfxge_tx_qinit(sc, SFXGE_TXQ_IP_CKSUM,
		    SFXGE_TXQ_IP_CKSUM, 0)) != 0)
			goto fail2;
	}

	for (index = 0;
	     index < sc->txq_count - SFXGE_EVQ0_N_TXQ(sc) + 1;
	     index++) {
		if ((rc = sfxge_tx_qinit(sc, SFXGE_EVQ0_N_TXQ(sc) - 1 + index,
		    SFXGE_TXQ_IP_TCP_UDP_CKSUM, index)) != 0)
			goto fail3;
	}

	sfxge_tx_stat_init(sc);

	return (0);

fail3:
	while (--index >= 0)
		sfxge_tx_qfini(sc, SFXGE_TXQ_IP_TCP_UDP_CKSUM + index);

	sfxge_tx_qfini(sc, SFXGE_TXQ_IP_CKSUM);

fail2:
	sfxge_tx_qfini(sc, SFXGE_TXQ_NON_CKSUM);

fail:
fail_txq_node:
	sc->txq_count = 0;
fail_tx_dpl_put_max:
fail_tx_dpl_get_non_tcp_max:
fail_tx_dpl_get_max:
	return (rc);
}