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
 scalar_t__ SMB_DATA ; 
 int SMB_ENOERR ; 
 int /*<<< orphan*/  SMB_PRTCL ; 
 int SMB_PRTCL_READ ; 
 int SMB_PRTCL_WORD_DATA ; 
 int /*<<< orphan*/  amdsmb_ec_read (struct amdsmb_softc*,scalar_t__,int*) ; 
 int /*<<< orphan*/  amdsmb_ec_write (struct amdsmb_softc*,int /*<<< orphan*/ ,int) ; 
 int amdsmb_wait (struct amdsmb_softc*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char,unsigned short,int) ; 

__attribute__((used)) static int
amdsmb_readw(device_t dev, u_char slave, char cmd, short *word)
{
	struct amdsmb_softc *sc = (struct amdsmb_softc *)device_get_softc(dev);
	u_char temp[2];
	int error;

	AMDSMB_LOCK(sc);
	amdsmb_ec_write(sc, SMB_CMD, cmd);
	amdsmb_ec_write(sc, SMB_ADDR, slave);
	amdsmb_ec_write(sc, SMB_PRTCL, SMB_PRTCL_READ | SMB_PRTCL_WORD_DATA);

	if ((error = amdsmb_wait(sc)) == SMB_ENOERR) {
		amdsmb_ec_read(sc, SMB_DATA + 0, &temp[0]);
		amdsmb_ec_read(sc, SMB_DATA + 1, &temp[1]);
		*word = temp[0] | (temp[1] << 8);
	}

	AMDSMB_DEBUG(printf("amdsmb: READW from 0x%x, cmd=0x%x, word=0x%x, "
	    "error=0x%x\n", slave, cmd, (unsigned short)*word, error));
	AMDSMB_UNLOCK(sc);

	return (error);
}