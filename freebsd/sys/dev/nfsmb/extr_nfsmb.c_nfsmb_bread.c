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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFSMB_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSMB_LOCK (struct nfsmb_softc*) ; 
 int NFSMB_SMBINB (struct nfsmb_softc*,scalar_t__) ; 
 int /*<<< orphan*/  NFSMB_SMBOUTB (struct nfsmb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFSMB_UNLOCK (struct nfsmb_softc*) ; 
 int /*<<< orphan*/  SMB_ADDR ; 
 scalar_t__ SMB_BCNT ; 
 int /*<<< orphan*/  SMB_CMD ; 
 scalar_t__ SMB_DATA ; 
 int SMB_EINVAL ; 
 int SMB_ENOERR ; 
 int /*<<< orphan*/  SMB_PRTCL ; 
 int SMB_PRTCL_BLOCK_DATA ; 
 int SMB_PRTCL_READ ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int nfsmb_wait (struct nfsmb_softc*) ; 
 int /*<<< orphan*/  printf (char*,int,int,char,int) ; 

__attribute__((used)) static int
nfsmb_bread(device_t dev, u_char slave, char cmd, u_char *count, char *buf)
{
	struct nfsmb_softc *sc = (struct nfsmb_softc *)device_get_softc(dev);
	u_char data, len, i;
	int error;

	if (*count < 1 || *count > 32)
		return (SMB_EINVAL);

	NFSMB_LOCK(sc);
	NFSMB_SMBOUTB(sc, SMB_CMD, cmd);
	NFSMB_SMBOUTB(sc, SMB_ADDR, slave);
	NFSMB_SMBOUTB(sc, SMB_PRTCL, SMB_PRTCL_READ | SMB_PRTCL_BLOCK_DATA);

	if ((error = nfsmb_wait(sc)) == SMB_ENOERR) {
		len = NFSMB_SMBINB(sc, SMB_BCNT);
		for (i = 0; i < len; i++) {
			data = NFSMB_SMBINB(sc, SMB_DATA + i);
			if (i < *count)
				buf[i] = data;
		}
		*count = len;
	}

	NFSMB_DEBUG(printf("nfsmb: READBLK to 0x%x, count=0x%x, cmd=0x%x, error=0x%x", slave, *count, cmd, error));
	NFSMB_UNLOCK(sc);

	return (error);
}