#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cclk; } ;
struct TYPE_6__ {TYPE_1__ vpd; int /*<<< orphan*/  rev; } ;
struct TYPE_7__ {TYPE_2__ params; int /*<<< orphan*/  tunq_coalesce; int /*<<< orphan*/  port_types; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  dev; } ;
typedef  TYPE_3__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb_debug ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txq_fills ; 

void
t3_add_attach_sysctls(adapter_t *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *children;

	ctx = device_get_sysctl_ctx(sc->dev);
	children = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev));

	/* random information */
	SYSCTL_ADD_STRING(ctx, children, OID_AUTO, 
	    "firmware_version",
	    CTLFLAG_RD, sc->fw_version,
	    0, "firmware version");
	SYSCTL_ADD_UINT(ctx, children, OID_AUTO,
	    "hw_revision",
	    CTLFLAG_RD, &sc->params.rev,
	    0, "chip model");
	SYSCTL_ADD_STRING(ctx, children, OID_AUTO, 
	    "port_types",
	    CTLFLAG_RD, sc->port_types,
	    0, "type of ports");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO, 
	    "enable_debug",
	    CTLFLAG_RW, &cxgb_debug,
	    0, "enable verbose debugging output");
	SYSCTL_ADD_UQUAD(ctx, children, OID_AUTO, "tunq_coalesce",
	    CTLFLAG_RD, &sc->tunq_coalesce,
	    "#tunneled packets freed");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO, 
	    "txq_overrun",
	    CTLFLAG_RD, &txq_fills,
	    0, "#times txq overrun");
	SYSCTL_ADD_UINT(ctx, children, OID_AUTO,
	    "core_clock",
	    CTLFLAG_RD, &sc->params.vpd.cclk,
	    0, "core clock frequency (in KHz)");
}