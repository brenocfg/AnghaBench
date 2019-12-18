#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tx_pauseframe_control; int rx_pauseframe_control; scalar_t__ tx_priority_flow_control; scalar_t__ rx_priority_flow_control; } ;
struct mlx5e_priv {TYPE_4__ params; int /*<<< orphan*/  ifp; int /*<<< orphan*/  sysctl_ifnet; int /*<<< orphan*/  sysctl_ctx; TYPE_3__* mdev; } ;
typedef  int /*<<< orphan*/  path ;
struct TYPE_7__ {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bsddev; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int /*<<< orphan*/  CTLFLAG_RDTUN ; 
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_U8 ; 
 int EINVAL ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PRIV_LOCK (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  PRIV_UNLOCK (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_en_err (int /*<<< orphan*/ ,char*) ; 
 int mlx5e_set_port_pause_and_pfc (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_sysctl_rx_priority_flow_control ; 
 int /*<<< orphan*/  mlx5e_sysctl_tx_priority_flow_control ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
mlx5e_setup_pauseframes(struct mlx5e_priv *priv)
{
#if (__FreeBSD_version < 1100000)
	char path[96];
#endif
	int error;

	/* enable pauseframes by default */
	priv->params.tx_pauseframe_control = 1;
	priv->params.rx_pauseframe_control = 1;

	/* disable ports flow control, PFC, by default */
	priv->params.tx_priority_flow_control = 0;
	priv->params.rx_priority_flow_control = 0;

#if (__FreeBSD_version < 1100000)
	/* compute path for sysctl */
	snprintf(path, sizeof(path), "dev.mce.%d.tx_pauseframe_control",
	    device_get_unit(priv->mdev->pdev->dev.bsddev));

	/* try to fetch tunable, if any */
	TUNABLE_INT_FETCH(path, &priv->params.tx_pauseframe_control);

	/* compute path for sysctl */
	snprintf(path, sizeof(path), "dev.mce.%d.rx_pauseframe_control",
	    device_get_unit(priv->mdev->pdev->dev.bsddev));

	/* try to fetch tunable, if any */
	TUNABLE_INT_FETCH(path, &priv->params.rx_pauseframe_control);
#endif

	/* register pauseframe SYSCTLs */
	SYSCTL_ADD_INT(&priv->sysctl_ctx, SYSCTL_CHILDREN(priv->sysctl_ifnet),
	    OID_AUTO, "tx_pauseframe_control", CTLFLAG_RDTUN,
	    &priv->params.tx_pauseframe_control, 0,
	    "Set to enable TX pause frames. Clear to disable.");

	SYSCTL_ADD_INT(&priv->sysctl_ctx, SYSCTL_CHILDREN(priv->sysctl_ifnet),
	    OID_AUTO, "rx_pauseframe_control", CTLFLAG_RDTUN,
	    &priv->params.rx_pauseframe_control, 0,
	    "Set to enable RX pause frames. Clear to disable.");

	/* register priority flow control, PFC, SYSCTLs */
	SYSCTL_ADD_PROC(&priv->sysctl_ctx, SYSCTL_CHILDREN(priv->sysctl_ifnet),
	    OID_AUTO, "tx_priority_flow_control", CTLTYPE_U8 | CTLFLAG_RWTUN |
	    CTLFLAG_MPSAFE, priv, 0, &mlx5e_sysctl_tx_priority_flow_control, "CU",
	    "Set to enable TX ports flow control frames for priorities 0..7. Clear to disable.");

	SYSCTL_ADD_PROC(&priv->sysctl_ctx, SYSCTL_CHILDREN(priv->sysctl_ifnet),
	    OID_AUTO, "rx_priority_flow_control", CTLTYPE_U8 | CTLFLAG_RWTUN |
	    CTLFLAG_MPSAFE, priv, 0, &mlx5e_sysctl_rx_priority_flow_control, "CU",
	    "Set to enable RX ports flow control frames for priorities 0..7. Clear to disable.");

	PRIV_LOCK(priv);

	/* range check */
	priv->params.tx_pauseframe_control =
	    priv->params.tx_pauseframe_control ? 1 : 0;
	priv->params.rx_pauseframe_control =
	    priv->params.rx_pauseframe_control ? 1 : 0;

	/* update firmware */
	error = mlx5e_set_port_pause_and_pfc(priv);
	if (error == -EINVAL) {
		mlx5_en_err(priv->ifp,
		    "Global pauseframes must be disabled before enabling PFC.\n");
		priv->params.rx_priority_flow_control = 0;
		priv->params.tx_priority_flow_control = 0;

		/* update firmware */
		(void) mlx5e_set_port_pause_and_pfc(priv);
	}
	PRIV_UNLOCK(priv);
}