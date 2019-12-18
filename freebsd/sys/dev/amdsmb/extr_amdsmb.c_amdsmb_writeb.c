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
struct amdsmb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDSMB_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDSMB_LOCK (struct amdsmb_softc*) ; 
 int /*<<< orphan*/  AMDSMB_UNLOCK (struct amdsmb_softc*) ; 
 int /*<<< orphan*/  SMB_ADDR ; 
 int /*<<< orphan*/  SMB_CMD ; 
 int /*<<< orphan*/  SMB_DATA ; 
 int /*<<< orphan*/  SMB_PRTCL ; 
 int SMB_PRTCL_BYTE_DATA ; 
 int SMB_PRTCL_WRITE ; 
 int /*<<< orphan*/  amdsmb_ec_write (struct amdsmb_softc*,int /*<<< orphan*/ ,int) ; 
 int amdsmb_wait (struct amdsmb_softc*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char,char,int) ; 

__attribute__((used)) static int
amdsmb_writeb(device_t dev, u_char slave, char cmd, char byte)
{
	struct amdsmb_softc *sc = (struct amdsmb_softc *)device_get_softc(dev);
	int error;

	AMDSMB_LOCK(sc);
	amdsmb_ec_write(sc, SMB_CMD, cmd);
	amdsmb_ec_write(sc, SMB_DATA, byte);
	amdsmb_ec_write(sc, SMB_ADDR, slave);
	amdsmb_ec_write(sc, SMB_PRTCL, SMB_PRTCL_WRITE | SMB_PRTCL_BYTE_DATA);

	error = amdsmb_wait(sc);

	AMDSMB_DEBUG(printf("amdsmb: WRITEB to 0x%x, cmd=0x%x, byte=0x%x, "
	    "error=0x%x\n", slave, cmd, byte, error));
	AMDSMB_UNLOCK(sc);

	return (error);
}