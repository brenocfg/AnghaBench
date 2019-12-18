#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct thread {int dummy; } ;
struct etherswitch_softc {int /*<<< orphan*/  sc_dev; } ;
struct cdev {struct etherswitch_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  etherswitch_vlangroup_t ;
struct TYPE_4__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ etherswitch_reg_t ;
struct TYPE_5__ {int /*<<< orphan*/  es_port; } ;
typedef  TYPE_2__ etherswitch_portid_t ;
typedef  int /*<<< orphan*/  etherswitch_port_t ;
struct TYPE_6__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; int /*<<< orphan*/  phy; } ;
typedef  TYPE_3__ etherswitch_phyreg_t ;
typedef  int /*<<< orphan*/  etherswitch_info_t ;
typedef  int /*<<< orphan*/  etherswitch_conf_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOTTY ; 
 int ETHERSWITCH_FETCH_TABLE (int /*<<< orphan*/ ,void*) ; 
 int ETHERSWITCH_FETCH_TABLE_ENTRY (int /*<<< orphan*/ ,void*) ; 
 int ETHERSWITCH_FLUSH_ALL (int /*<<< orphan*/ ) ; 
 int ETHERSWITCH_FLUSH_PORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETHERSWITCH_GETCONF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ETHERSWITCH_GETINFO (int /*<<< orphan*/ ) ; 
 int ETHERSWITCH_GETPORT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ETHERSWITCH_GETVGROUP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ETHERSWITCH_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETHERSWITCH_READPHYREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETHERSWITCH_READREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETHERSWITCH_SETCONF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ETHERSWITCH_SETPORT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ETHERSWITCH_SETVGROUP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ETHERSWITCH_UNLOCK (int /*<<< orphan*/ ) ; 
 int ETHERSWITCH_WRITEPHYREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETHERSWITCH_WRITEREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IOETHERSWITCHFLUSHALL 142 
#define  IOETHERSWITCHFLUSHPORT 141 
#define  IOETHERSWITCHGETCONF 140 
#define  IOETHERSWITCHGETINFO 139 
#define  IOETHERSWITCHGETPHYREG 138 
#define  IOETHERSWITCHGETPORT 137 
#define  IOETHERSWITCHGETREG 136 
#define  IOETHERSWITCHGETTABLE 135 
#define  IOETHERSWITCHGETTABLEENTRY 134 
#define  IOETHERSWITCHGETVLANGROUP 133 
#define  IOETHERSWITCHSETCONF 132 
#define  IOETHERSWITCHSETPHYREG 131 
#define  IOETHERSWITCHSETPORT 130 
#define  IOETHERSWITCHSETREG 129 
#define  IOETHERSWITCHSETVLANGROUP 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
etherswitchioctl(struct cdev *cdev, u_long cmd, caddr_t data, int flags, struct thread *td)
{
	struct etherswitch_softc *sc = cdev->si_drv1;
	device_t dev = sc->sc_dev;
	device_t etherswitch = device_get_parent(dev);
	etherswitch_conf_t conf;
	etherswitch_info_t *info;
	etherswitch_reg_t *reg;
	etherswitch_phyreg_t *phyreg;
	etherswitch_portid_t *portid;
	int error = 0;

	switch (cmd) {
	case IOETHERSWITCHGETINFO:
		info = ETHERSWITCH_GETINFO(etherswitch);
		bcopy(info, data, sizeof(etherswitch_info_t));
		break;
		
	case IOETHERSWITCHGETREG:
		reg = (etherswitch_reg_t *)data;
		ETHERSWITCH_LOCK(etherswitch);
		reg->val = ETHERSWITCH_READREG(etherswitch, reg->reg);
		ETHERSWITCH_UNLOCK(etherswitch);
		break;
	
	case IOETHERSWITCHSETREG:
		reg = (etherswitch_reg_t *)data;
		ETHERSWITCH_LOCK(etherswitch);
		error = ETHERSWITCH_WRITEREG(etherswitch, reg->reg, reg->val);
		ETHERSWITCH_UNLOCK(etherswitch);
		break;

	case IOETHERSWITCHGETPORT:
		error = ETHERSWITCH_GETPORT(etherswitch, (etherswitch_port_t *)data);
		break;

	case IOETHERSWITCHSETPORT:
		error = ETHERSWITCH_SETPORT(etherswitch, (etherswitch_port_t *)data);
		break;

	case IOETHERSWITCHGETVLANGROUP:
		error = ETHERSWITCH_GETVGROUP(etherswitch, (etherswitch_vlangroup_t *)data);
		break;

	case IOETHERSWITCHSETVLANGROUP:
		error = ETHERSWITCH_SETVGROUP(etherswitch, (etherswitch_vlangroup_t *)data);
		break;

	case IOETHERSWITCHGETPHYREG:
		phyreg = (etherswitch_phyreg_t *)data;
		phyreg->val = ETHERSWITCH_READPHYREG(etherswitch, phyreg->phy, phyreg->reg);
		break;
	
	case IOETHERSWITCHSETPHYREG:
		phyreg = (etherswitch_phyreg_t *)data;
		error = ETHERSWITCH_WRITEPHYREG(etherswitch, phyreg->phy, phyreg->reg, phyreg->val);
		break;

	case IOETHERSWITCHGETCONF:
		bzero(&conf, sizeof(etherswitch_conf_t));
		error = ETHERSWITCH_GETCONF(etherswitch, &conf);
		bcopy(&conf, data, sizeof(etherswitch_conf_t));
		break;

	case IOETHERSWITCHSETCONF:
		error = ETHERSWITCH_SETCONF(etherswitch, (etherswitch_conf_t *)data);
		break;

	case IOETHERSWITCHFLUSHALL:
		error = ETHERSWITCH_FLUSH_ALL(etherswitch);
		break;

	case IOETHERSWITCHFLUSHPORT:
		portid = (etherswitch_portid_t *)data;
		error = ETHERSWITCH_FLUSH_PORT(etherswitch, portid->es_port);
		break;

	case IOETHERSWITCHGETTABLE:
		error = ETHERSWITCH_FETCH_TABLE(etherswitch, (void *) data);
		break;

	case IOETHERSWITCHGETTABLEENTRY:
		error = ETHERSWITCH_FETCH_TABLE_ENTRY(etherswitch, (void *) data);
		break;

	default:
		error = ENOTTY;
	}

	return (error);
}