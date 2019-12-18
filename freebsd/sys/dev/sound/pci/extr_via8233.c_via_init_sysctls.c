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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  dev ;

/* Variables and functions */
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_via8233_dxs_src ; 
 int /*<<< orphan*/  sysctl_via8233_spdif_enable ; 
 int /*<<< orphan*/  sysctl_via_polling ; 

__attribute__((used)) static void
via_init_sysctls(device_t dev)
{
	/* XXX: an user should be able to set this with a control tool,
	   if not done before 7.0-RELEASE, this needs to be converted to
	   a device specific sysctl "dev.pcm.X.yyy" via device_get_sysctl_*()
	   as discussed on multimedia@ in msg-id <861wujij2q.fsf@xps.des.no> */
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "spdif_enabled",  CTLTYPE_INT | CTLFLAG_RW, dev, sizeof(dev),
	    sysctl_via8233_spdif_enable, "I",
	    "Enable S/PDIF output on primary playback channel");
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "dxs_src", CTLTYPE_INT | CTLFLAG_RW, dev, sizeof(dev),
	    sysctl_via8233_dxs_src, "I",
	    "Enable VIA DXS Sample Rate Converter");
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "polling", CTLTYPE_INT | CTLFLAG_RW, dev, sizeof(dev),
	    sysctl_via_polling, "I",
	    "Enable polling mode");
}