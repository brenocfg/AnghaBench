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
typedef  int /*<<< orphan*/  vmbus_chan_callback_t ;
struct vmbus_ic_softc {int /*<<< orphan*/  ic_buf; int /*<<< orphan*/  ic_buflen; int /*<<< orphan*/  ic_dev; } ;
struct vmbus_channel {int dummy; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct vmbus_ic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMBUS_IC_BRSIZE ; 
 struct vmbus_ic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vmbus_chan_open (struct vmbus_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmbus_ic_softc*) ; 
 int /*<<< orphan*/  vmbus_chan_set_readbatch (struct vmbus_channel*,int) ; 
 struct vmbus_channel* vmbus_get_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_ic_fwver_sysctl ; 
 int /*<<< orphan*/  vmbus_ic_msgver_sysctl ; 

int
vmbus_ic_attach(device_t dev, vmbus_chan_callback_t cb)
{
	struct vmbus_ic_softc *sc = device_get_softc(dev);
	struct vmbus_channel *chan = vmbus_get_channel(dev);
	struct sysctl_oid_list *child;
	struct sysctl_ctx_list *ctx;
	int error;

	sc->ic_dev = dev;
	sc->ic_buflen = VMBUS_IC_BRSIZE;
	sc->ic_buf = malloc(VMBUS_IC_BRSIZE, M_DEVBUF, M_WAITOK | M_ZERO);

	/*
	 * These services are not performance critical and do not need
	 * batched reading. Furthermore, some services such as KVP can
	 * only handle one message from the host at a time.
	 * Turn off batched reading for all util drivers before we open the
	 * channel.
	 */
	vmbus_chan_set_readbatch(chan, false);

	error = vmbus_chan_open(chan, VMBUS_IC_BRSIZE, VMBUS_IC_BRSIZE, NULL, 0,
	    cb, sc);
	if (error) {
		free(sc->ic_buf, M_DEVBUF);
		return (error);
	}

	ctx = device_get_sysctl_ctx(dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "fw_version",
	    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    vmbus_ic_fwver_sysctl, "A", "framework version");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "msg_version",
	    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    vmbus_ic_msgver_sysctl, "A", "message version");

	return (0);
}