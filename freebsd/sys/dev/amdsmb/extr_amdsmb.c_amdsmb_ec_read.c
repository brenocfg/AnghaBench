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
typedef  int /*<<< orphan*/  u_char ;
struct amdsmb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDSMB_ECINB (struct amdsmb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDSMB_ECOUTB (struct amdsmb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDSMB_LOCK_ASSERT (struct amdsmb_softc*) ; 
 int /*<<< orphan*/  EC_CMD ; 
 int /*<<< orphan*/  EC_CMD_RD ; 
 int /*<<< orphan*/  EC_DATA ; 
 scalar_t__ amdsmb_ec_wait_read (struct amdsmb_softc*) ; 
 scalar_t__ amdsmb_ec_wait_write (struct amdsmb_softc*) ; 

__attribute__((used)) static int
amdsmb_ec_read(struct amdsmb_softc *sc, u_char addr, u_char *data)
{

	AMDSMB_LOCK_ASSERT(sc);
	if (amdsmb_ec_wait_write(sc))
		return (1);
	AMDSMB_ECOUTB(sc, EC_CMD, EC_CMD_RD);

	if (amdsmb_ec_wait_write(sc))
		return (1);
	AMDSMB_ECOUTB(sc, EC_DATA, addr);

	if (amdsmb_ec_wait_read(sc))
		return (1);
	*data = AMDSMB_ECINB(sc, EC_DATA);

	return (0);
}