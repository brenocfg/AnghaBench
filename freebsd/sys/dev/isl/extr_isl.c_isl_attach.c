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
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct isl_softc {int /*<<< orphan*/  isl_sx; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD1_MASK_ALS_ONCE ; 
 int /*<<< orphan*/  CMD1_MASK_IR_ONCE ; 
 int /*<<< orphan*/  CMD1_MASK_PROX_ONCE ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  ISL_METHOD_ALS ; 
 int /*<<< orphan*/  ISL_METHOD_IR ; 
 int /*<<< orphan*/  ISL_METHOD_PROX ; 
 int /*<<< orphan*/  ISL_METHOD_RANGE ; 
 int /*<<< orphan*/  ISL_METHOD_RESOLUTION ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct isl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct isl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 scalar_t__ init_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isl_read_sensor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isl_sysctl ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
isl_attach(device_t dev)
{
	struct isl_softc *sc;
	struct sysctl_ctx_list *sysctl_ctx;
	struct sysctl_oid *sysctl_tree;
	int use_als;
	int use_ir;
	int use_prox;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (init_device(dev, 0) != 0)
		return (ENXIO);

	sx_init(&sc->isl_sx, "ISL read lock");

	sysctl_ctx = device_get_sysctl_ctx(dev);
	sysctl_tree = device_get_sysctl_tree(dev);

	use_als = isl_read_sensor(dev, CMD1_MASK_ALS_ONCE) >= 0;
	use_ir = isl_read_sensor(dev, CMD1_MASK_IR_ONCE) >= 0;
	use_prox = isl_read_sensor(dev, CMD1_MASK_PROX_ONCE) >= 0;

	if (use_als) {
		SYSCTL_ADD_PROC(sysctl_ctx,
			SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
			    "als", CTLTYPE_INT | CTLFLAG_RD,
			    sc, ISL_METHOD_ALS, isl_sysctl, "I",
			    "Current ALS sensor read-out");
	}

	if (use_ir) {
		SYSCTL_ADD_PROC(sysctl_ctx,
			SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
			    "ir", CTLTYPE_INT | CTLFLAG_RD,
			    sc, ISL_METHOD_IR, isl_sysctl, "I",
			    "Current IR sensor read-out");
	}

	if (use_prox) {
		SYSCTL_ADD_PROC(sysctl_ctx,
			SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
			    "prox", CTLTYPE_INT | CTLFLAG_RD,
			    sc, ISL_METHOD_PROX, isl_sysctl, "I",
			    "Current proximity sensor read-out");
	}

	SYSCTL_ADD_PROC(sysctl_ctx,
		SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
		    "resolution", CTLTYPE_INT | CTLFLAG_RD,
		    sc, ISL_METHOD_RESOLUTION, isl_sysctl, "I",
		    "Current proximity sensor resolution");

	SYSCTL_ADD_PROC(sysctl_ctx,
	SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
	    "range", CTLTYPE_INT | CTLFLAG_RD,
	    sc, ISL_METHOD_RANGE, isl_sysctl, "I",
	    "Current proximity sensor range");

	return (0);
}