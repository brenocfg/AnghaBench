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
typedef  int uint32_t ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct am335x_scm_softc {int /*<<< orphan*/  sc_temp_oid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int SCM_BGAP_CLRZ ; 
 int SCM_BGAP_CONTCONV ; 
 int /*<<< orphan*/  SCM_BGAP_CTRL ; 
 int SCM_BGAP_SOC ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am335x_scm_temp_sysctl ; 
 struct am335x_scm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_scm_reg_read_4 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ti_scm_reg_write_4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
am335x_scm_attach(device_t dev)
{
	struct am335x_scm_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *tree;
	uint32_t reg;

	/* Reset the digital outputs. */
	ti_scm_reg_write_4(SCM_BGAP_CTRL, 0);
	ti_scm_reg_read_4(SCM_BGAP_CTRL, &reg);
	DELAY(500);
	/* Set continous mode. */
	ti_scm_reg_write_4(SCM_BGAP_CTRL, SCM_BGAP_CONTCONV);
	ti_scm_reg_read_4(SCM_BGAP_CTRL, &reg);
	DELAY(500);
	/* Start the ADC conversion. */
	reg = SCM_BGAP_CLRZ | SCM_BGAP_CONTCONV | SCM_BGAP_SOC;
	ti_scm_reg_write_4(SCM_BGAP_CTRL, reg);

	/* Temperature sysctl. */
	sc = device_get_softc(dev);
        ctx = device_get_sysctl_ctx(dev);
	tree = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	sc->sc_temp_oid = SYSCTL_ADD_PROC(ctx, tree, OID_AUTO,
	    "temperature", CTLTYPE_INT | CTLFLAG_RD | CTLFLAG_MPSAFE,
	    dev, 0, am335x_scm_temp_sysctl, "IK", "Current temperature");

	return (0);
}