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
typedef  int u_char ;
struct nfsmb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  NFSMB_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSMB_LOCK_ASSERT (struct nfsmb_softc*) ; 
 int NFSMB_SMBINB (struct nfsmb_softc*,int /*<<< orphan*/ ) ; 
 int SMB_EBUSERR ; 
 int SMB_EBUSY ; 
 int SMB_ENOACK ; 
 int SMB_ENOERR ; 
 int SMB_ENOTSUPP ; 
 int SMB_ETIMEOUT ; 
 int /*<<< orphan*/  SMB_PRTCL ; 
 int /*<<< orphan*/  SMB_STS ; 
#define  SMB_STS_B 134 
#define  SMB_STS_DAD 133 
#define  SMB_STS_DANA 132 
#define  SMB_STS_DCAD 131 
#define  SMB_STS_HUP 130 
#define  SMB_STS_OK 129 
 int SMB_STS_STATUS ; 
#define  SMB_STS_T 128 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
nfsmb_wait(struct nfsmb_softc *sc)
{
	u_char sts;
	int error, count;

	NFSMB_LOCK_ASSERT(sc);
	if (NFSMB_SMBINB(sc, SMB_PRTCL) != 0)
	{
		count = 10000;
		do {
			DELAY(500);
		} while (NFSMB_SMBINB(sc, SMB_PRTCL) != 0 && count--);
		if (count == 0)
			return (SMB_ETIMEOUT);
	}

	sts = NFSMB_SMBINB(sc, SMB_STS) & SMB_STS_STATUS;
	NFSMB_DEBUG(printf("nfsmb: STS=0x%x\n", sts));

	switch (sts) {
	case SMB_STS_OK:
		error = SMB_ENOERR;
		break;
	case SMB_STS_DANA:
		error = SMB_ENOACK;
		break;
	case SMB_STS_B:
		error = SMB_EBUSY;
		break;
	case SMB_STS_T:
		error = SMB_ETIMEOUT;
		break;
	case SMB_STS_DCAD:
	case SMB_STS_DAD:
	case SMB_STS_HUP:
		error = SMB_ENOTSUPP;
		break;
	default:
		error = SMB_EBUSERR;
		break;
	}

	return (error);
}