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
typedef  scalar_t__ u_char ;
struct amdsmb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDSMB_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDSMB_LOCK_ASSERT (struct amdsmb_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
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
 scalar_t__ SMB_STS_STATUS ; 
#define  SMB_STS_T 128 
 int /*<<< orphan*/  amdsmb_ec_read (struct amdsmb_softc*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

__attribute__((used)) static int
amdsmb_wait(struct amdsmb_softc *sc)
{
	u_char sts, temp;
	int error, count;

	AMDSMB_LOCK_ASSERT(sc);
	amdsmb_ec_read(sc, SMB_PRTCL, &temp);
	if (temp != 0)
	{
		count = 10000;
		do {
			DELAY(500);
			amdsmb_ec_read(sc, SMB_PRTCL, &temp);
		} while (temp != 0 && count--);
		if (count == 0)
			return (SMB_ETIMEOUT);
	}

	amdsmb_ec_read(sc, SMB_STS, &sts);
	sts &= SMB_STS_STATUS;
	AMDSMB_DEBUG(printf("amdsmb: STS=0x%x\n", sts));

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