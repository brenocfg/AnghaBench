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
struct TYPE_3__ {int /*<<< orphan*/  fw_ver_str; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_1__ qla_host_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 scalar_t__ dbg_level ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 scalar_t__ free_pkt_thres ; 
 scalar_t__ jumbo_replenish ; 
 int /*<<< orphan*/  qla_sysctl_get_stats ; 
 scalar_t__ rcv_pkt_thres ; 
 scalar_t__ rcv_pkt_thres_d ; 
 scalar_t__ snd_pkt_thres ; 
 scalar_t__ std_replenish ; 

__attribute__((used)) static void
qla_add_sysctls(qla_host_t *ha)
{
        device_t dev = ha->pci_dev;

        SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "stats", CTLTYPE_INT | CTLFLAG_RD,
                (void *)ha, 0,
                qla_sysctl_get_stats, "I", "Statistics");

	SYSCTL_ADD_STRING(device_get_sysctl_ctx(dev),
		SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
		OID_AUTO, "fw_version", CTLFLAG_RD,
		ha->fw_ver_str, 0, "firmware version");

	dbg_level = 0;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "debug", CTLFLAG_RW,
                &dbg_level, dbg_level, "Debug Level");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "std_replenish", CTLFLAG_RW,
                &std_replenish, std_replenish,
                "Threshold for Replenishing Standard Frames");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "jumbo_replenish", CTLFLAG_RW,
                &jumbo_replenish, jumbo_replenish,
                "Threshold for Replenishing Jumbo Frames");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "rcv_pkt_thres",  CTLFLAG_RW,
                &rcv_pkt_thres, rcv_pkt_thres,
                "Threshold for # of rcv pkts to trigger indication isr");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "rcv_pkt_thres_d",  CTLFLAG_RW,
                &rcv_pkt_thres_d, rcv_pkt_thres_d,
                "Threshold for # of rcv pkts to trigger indication defered");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "snd_pkt_thres",  CTLFLAG_RW,
                &snd_pkt_thres, snd_pkt_thres,
                "Threshold for # of snd packets");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "free_pkt_thres",  CTLFLAG_RW,
                &free_pkt_thres, free_pkt_thres,
                "Threshold for # of packets to free at a time");

        return;
}