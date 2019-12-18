#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ifnet {struct an_softc* if_softc; } ;
struct TYPE_2__ {int an_len; unsigned short an_type; int an_val; } ;
struct an_softc {TYPE_1__ areq; } ;
struct an_ltv_gen {int dummy; } ;
struct aironet_ioctl {int command; int len; scalar_t__ data; } ;

/* Variables and functions */
#define  AIROGCAP 138 
#define  AIROGCFG 137 
#define  AIROGDRVNAM 136 
#define  AIROGEHTENC 135 
#define  AIROGSLIST 134 
#define  AIROGSTAT 133 
#define  AIROGSTATSC32 132 
#define  AIROGSTATSD32 131 
#define  AIROGVLIST 130 
#define  AIROGWEPKNV 129 
#define  AIROGWEPKTMP 128 
 int /*<<< orphan*/  AN_LOCK (struct an_softc*) ; 
 int AN_MAX_DATALEN ; 
 unsigned short AN_RID_32BITS_CUM ; 
 unsigned short AN_RID_32BITS_DELTA ; 
 unsigned short AN_RID_APLIST ; 
 unsigned short AN_RID_CAPABILITIES ; 
 unsigned short AN_RID_DRVNAME ; 
 unsigned short AN_RID_ENCAPPROTO ; 
 unsigned short AN_RID_GENCONFIG ; 
 unsigned short AN_RID_SSIDLIST ; 
 unsigned short AN_RID_STATUS ; 
 unsigned short AN_RID_WEP_PERM ; 
 unsigned short AN_RID_WEP_TEMP ; 
 int /*<<< orphan*/  AN_UNLOCK (struct an_softc*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  an_read_record (struct an_softc*,struct an_ltv_gen*) ; 
 scalar_t__ copyout (int*,scalar_t__,int) ; 

__attribute__((used)) static int
readrids(struct ifnet *ifp, struct aironet_ioctl *l_ioctl)
{
	unsigned short  rid;
	struct an_softc *sc;
	int error;

	switch (l_ioctl->command) {
	case AIROGCAP:
		rid = AN_RID_CAPABILITIES;
		break;
	case AIROGCFG:
		rid = AN_RID_GENCONFIG;
		break;
	case AIROGSLIST:
		rid = AN_RID_SSIDLIST;
		break;
	case AIROGVLIST:
		rid = AN_RID_APLIST;
		break;
	case AIROGDRVNAM:
		rid = AN_RID_DRVNAME;
		break;
	case AIROGEHTENC:
		rid = AN_RID_ENCAPPROTO;
		break;
	case AIROGWEPKTMP:
		rid = AN_RID_WEP_TEMP;
		break;
	case AIROGWEPKNV:
		rid = AN_RID_WEP_PERM;
		break;
	case AIROGSTAT:
		rid = AN_RID_STATUS;
		break;
	case AIROGSTATSD32:
		rid = AN_RID_32BITS_DELTA;
		break;
	case AIROGSTATSC32:
		rid = AN_RID_32BITS_CUM;
		break;
	default:
		rid = 999;
		break;
	}

	if (rid == 999)	/* Is bad command */
		return -EINVAL;

	sc = ifp->if_softc;
	sc->areq.an_len  = AN_MAX_DATALEN;
	sc->areq.an_type = rid;

	an_read_record(sc, (struct an_ltv_gen *)&sc->areq);

	l_ioctl->len = sc->areq.an_len - 4;	/* just data */

	AN_UNLOCK(sc);
	/* the data contains the length at first */
	if (copyout(&(sc->areq.an_len), l_ioctl->data,
		    sizeof(sc->areq.an_len))) {
		error = -EFAULT;
		goto lock_exit;
	}
	/* Just copy the data back */
	if (copyout(&(sc->areq.an_val), l_ioctl->data + 2,
		    l_ioctl->len)) {
		error = -EFAULT;
		goto lock_exit;
	}
	error = 0;
lock_exit:
	AN_LOCK(sc);
	return (error);
}