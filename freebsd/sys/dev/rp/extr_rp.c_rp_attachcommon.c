#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tty {int dummy; } ;
struct rp_port {int rp_port; int rp_unit; int rp_chan; int rp_aiop; int rp_intmask; int rp_cts; int /*<<< orphan*/  rp_channel; TYPE_1__* rp_ctlp; int /*<<< orphan*/  rp_timer; struct tty* rp_tty; } ;
struct TYPE_6__ {int num_ports; int hwmtx_init; int /*<<< orphan*/  hwmtx; int /*<<< orphan*/  dev; struct rp_port* rp; } ;
typedef  TYPE_1__ CONTROLLER_T ;

/* Variables and functions */
 int CTS_ACT ; 
 int DELTA_CD ; 
 int DELTA_CTS ; 
 int DELTA_DSR ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int RXF_TRIG ; 
 char* RocketPortVersion ; 
 int SRC_INT ; 
 int TXFIFO_MT ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*,int) ; 
 int /*<<< orphan*/  rp_releaseresource (TYPE_1__*) ; 
 int /*<<< orphan*/  rp_tty_class ; 
 int sGetAiopNumChan (TYPE_1__*,int) ; 
 int sGetChanStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ sInitChan (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 struct tty* tty_alloc (int /*<<< orphan*/ *,struct rp_port*) ; 
 int /*<<< orphan*/  tty_getlock (struct tty*) ; 
 int /*<<< orphan*/  tty_makedev (struct tty*,int /*<<< orphan*/ *,char*,int,int) ; 

int
rp_attachcommon(CONTROLLER_T *ctlp, int num_aiops, int num_ports)
{
	int	unit;
	int	num_chan;
	int	aiop, chan, port;
	int	ChanStatus;
	int	retval;
	struct	rp_port *rp;
	struct tty *tp;

	unit = device_get_unit(ctlp->dev);

	printf("RocketPort%d (Version %s) %d ports.\n", unit,
		RocketPortVersion, num_ports);

	ctlp->num_ports = num_ports;
	ctlp->rp = rp = (struct rp_port *)
		malloc(sizeof(struct rp_port) * num_ports, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (rp == NULL) {
		device_printf(ctlp->dev, "rp_attachcommon: Could not malloc rp_ports structures.\n");
		retval = ENOMEM;
		goto nogo;
	}

	port = 0;
	for(aiop=0; aiop < num_aiops; aiop++) {
		num_chan = sGetAiopNumChan(ctlp, aiop);
		for(chan=0; chan < num_chan; chan++, port++, rp++) {
			rp->rp_tty = tp = tty_alloc(&rp_tty_class, rp);
			callout_init_mtx(&rp->rp_timer, tty_getlock(tp), 0);
			rp->rp_port = port;
			rp->rp_ctlp = ctlp;
			rp->rp_unit = unit;
			rp->rp_chan = chan;
			rp->rp_aiop = aiop;

			rp->rp_intmask = RXF_TRIG | TXFIFO_MT | SRC_INT |
				DELTA_CD | DELTA_CTS | DELTA_DSR;
#ifdef notdef
			ChanStatus = sGetChanStatus(&rp->rp_channel);
#endif /* notdef */
			if(sInitChan(ctlp, &rp->rp_channel, aiop, chan) == 0) {
				device_printf(ctlp->dev, "RocketPort sInitChan(%d, %d, %d) failed.\n",
					      unit, aiop, chan);
				retval = ENXIO;
				goto nogo;
			}
			ChanStatus = sGetChanStatus(&rp->rp_channel);
			rp->rp_cts = (ChanStatus & CTS_ACT) != 0;
			tty_makedev(tp, NULL, "R%r%r", unit, port);
		}
	}

	mtx_init(&ctlp->hwmtx, "rp_hwmtx", NULL, MTX_DEF);
	ctlp->hwmtx_init = 1;
	return (0);

nogo:
	rp_releaseresource(ctlp);

	return (retval);
}