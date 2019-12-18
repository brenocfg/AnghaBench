#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  bsddev; } ;
struct pci_dev {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * error_counters; int /*<<< orphan*/ * status_counters; } ;
struct mlx5_priv {int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  ctx_list; TYPE_2__ pme_stats; int /*<<< orphan*/  pci_dev_data; } ;
struct mlx5_core_dev {int /*<<< orphan*/  sysctl_ctx; int /*<<< orphan*/  dump_lock; int /*<<< orphan*/  intf_state_mutex; int /*<<< orphan*/  pci_status_mutex; struct mlx5_priv priv; int /*<<< orphan*/  pwr_value; int /*<<< orphan*/  pwr_status; int /*<<< orphan*/  msix_eqvec; int /*<<< orphan*/  event; struct pci_dev* pdev; int /*<<< orphan*/ * profile; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RDTUN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t MLX5_DEFAULT_PROF ; 
 int MLX5_MODULE_EVENT_ERROR_NUM ; 
 size_t MLX5_MODULE_STATUS_PLUGGED_ENABLED ; 
 size_t MLX5_MODULE_STATUS_UNPLUGGED ; 
 int MTX_DEF ; 
 int MTX_NEW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_core_dev*) ; 
 struct mlx5_core_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_core_event ; 
 int /*<<< orphan*/  mlx5_firmware_update (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fwdump_prep (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_health_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_health_init (struct mlx5_core_dev*) ; 
 int mlx5_load_one (struct mlx5_core_dev*,struct mlx5_priv*,int) ; 
 int /*<<< orphan*/  mlx5_pagealloc_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pagealloc_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pci_close (struct mlx5_core_dev*,struct mlx5_priv*) ; 
 int mlx5_pci_init (struct mlx5_core_dev*,struct mlx5_priv*) ; 
 char** mlx5_pme_err_desc ; 
 size_t mlx5_prof_sel ; 
 int /*<<< orphan*/  mlx5_version ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * profiles ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_one(struct pci_dev *pdev,
		    const struct pci_device_id *id)
{
	struct mlx5_core_dev *dev;
	struct mlx5_priv *priv;
	device_t bsddev = pdev->dev.bsddev;
	int i,err;
	struct sysctl_oid *pme_sysctl_node;
	struct sysctl_oid *pme_err_sysctl_node;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	priv = &dev->priv;
	if (id)
		priv->pci_dev_data = id->driver_data;

	if (mlx5_prof_sel < 0 || mlx5_prof_sel >= ARRAY_SIZE(profiles)) {
		device_printf(bsddev,
		    "WARN: selected profile out of range, selecting default (%d)\n",
		    MLX5_DEFAULT_PROF);
		mlx5_prof_sel = MLX5_DEFAULT_PROF;
	}
	dev->profile = &profiles[mlx5_prof_sel];
	dev->pdev = pdev;
	dev->event = mlx5_core_event;

	/* Set desc */
	device_set_desc(bsddev, mlx5_version);

	sysctl_ctx_init(&dev->sysctl_ctx);
	SYSCTL_ADD_INT(&dev->sysctl_ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(bsddev)),
	    OID_AUTO, "msix_eqvec", CTLFLAG_RDTUN, &dev->msix_eqvec, 0,
	    "Maximum number of MSIX event queue vectors, if set");
	SYSCTL_ADD_INT(&dev->sysctl_ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(bsddev)),
	    OID_AUTO, "power_status", CTLFLAG_RD, &dev->pwr_status, 0,
	    "0:Invalid 1:Sufficient 2:Insufficient");
	SYSCTL_ADD_INT(&dev->sysctl_ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(bsddev)),
	    OID_AUTO, "power_value", CTLFLAG_RD, &dev->pwr_value, 0,
	    "Current power value in Watts");

	pme_sysctl_node = SYSCTL_ADD_NODE(&dev->sysctl_ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(bsddev)),
	    OID_AUTO, "pme_stats", CTLFLAG_RD, NULL,
	    "Port module event statistics");
	if (pme_sysctl_node == NULL) {
		err = -ENOMEM;
		goto clean_sysctl_ctx;
	}
	pme_err_sysctl_node = SYSCTL_ADD_NODE(&dev->sysctl_ctx,
	    SYSCTL_CHILDREN(pme_sysctl_node),
	    OID_AUTO, "errors", CTLFLAG_RD, NULL,
	    "Port module event error statistics");
	if (pme_err_sysctl_node == NULL) {
		err = -ENOMEM;
		goto clean_sysctl_ctx;
	}
	SYSCTL_ADD_U64(&dev->sysctl_ctx,
	    SYSCTL_CHILDREN(pme_sysctl_node), OID_AUTO,
	    "module_plug", CTLFLAG_RD | CTLFLAG_MPSAFE,
	    &dev->priv.pme_stats.status_counters[MLX5_MODULE_STATUS_PLUGGED_ENABLED],
	    0, "Number of time module plugged");
	SYSCTL_ADD_U64(&dev->sysctl_ctx,
	    SYSCTL_CHILDREN(pme_sysctl_node), OID_AUTO,
	    "module_unplug", CTLFLAG_RD | CTLFLAG_MPSAFE,
	    &dev->priv.pme_stats.status_counters[MLX5_MODULE_STATUS_UNPLUGGED],
	    0, "Number of time module unplugged");
	for (i = 0 ; i < MLX5_MODULE_EVENT_ERROR_NUM; i++) {
		SYSCTL_ADD_U64(&dev->sysctl_ctx,
		    SYSCTL_CHILDREN(pme_err_sysctl_node), OID_AUTO,
		    mlx5_pme_err_desc[2 * i], CTLFLAG_RD | CTLFLAG_MPSAFE,
		    &dev->priv.pme_stats.error_counters[i],
		    0, mlx5_pme_err_desc[2 * i + 1]);
	}


	INIT_LIST_HEAD(&priv->ctx_list);
	spin_lock_init(&priv->ctx_lock);
	mutex_init(&dev->pci_status_mutex);
	mutex_init(&dev->intf_state_mutex);
	mtx_init(&dev->dump_lock, "mlx5dmp", NULL, MTX_DEF | MTX_NEW);
	err = mlx5_pci_init(dev, priv);
	if (err) {
		mlx5_core_err(dev, "mlx5_pci_init failed %d\n", err);
		goto clean_dev;
	}

	err = mlx5_health_init(dev);
	if (err) {
		mlx5_core_err(dev, "mlx5_health_init failed %d\n", err);
		goto close_pci;
	}

	mlx5_pagealloc_init(dev);

	err = mlx5_load_one(dev, priv, true);
	if (err) {
		mlx5_core_err(dev, "mlx5_load_one failed %d\n", err);
		goto clean_health;
	}

	mlx5_fwdump_prep(dev);

	mlx5_firmware_update(dev);

	pci_save_state(bsddev);
	return 0;

clean_health:
	mlx5_pagealloc_cleanup(dev);
	mlx5_health_cleanup(dev);
close_pci:
	mlx5_pci_close(dev, priv);
clean_dev:
	mtx_destroy(&dev->dump_lock);
clean_sysctl_ctx:
	sysctl_ctx_free(&dev->sysctl_ctx);
	kfree(dev);
	return err;
}