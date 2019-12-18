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
 char NFSMB_SMBINB (struct nfsmb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSMB_SMBOUTB (struct nfsmb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFSMB_UNLOCK (struct nfsmb_softc*) ; 
 int /*<<< orphan*/  SMB_ADDR ; 
 int /*<<< orphan*/  SMB_DATA ; 
 int SMB_ENOERR ; 
 int /*<<< orphan*/  SMB_PRTCL ; 
 int SMB_PRTCL_BYTE ; 
 int SMB_PRTCL_READ ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int nfsmb_wait (struct nfsmb_softc*) ; 
 int /*<<< orphan*/  printf (char*,int,char,int) ; 

__attribute__((used)) static int
nfsmb_recvb(device_t dev, u_char slave, char *byte)
{
	struct nfsmb_softc *sc = (struct nfsmb_softc *)device_get_softc(dev);
	int error;

	NFSMB_LOCK(sc);
	NFSMB_SMBOUTB(sc, SMB_ADDR, slave);
	NFSMB_SMBOUTB(sc, SMB_PRTCL, SMB_PRTCL_READ | SMB_PRTCL_BYTE);

	if ((error = nfsmb_wait(sc)) == SMB_ENOERR)
		*byte = NFSMB_SMBINB(sc, SMB_DATA);

	NFSMB_DEBUG(printf("nfsmb: RECVB from 0x%x, byte=0x%x, error=0x%x\n", slave, *byte, error));
	NFSMB_UNLOCK(sc);

	return (error);
}