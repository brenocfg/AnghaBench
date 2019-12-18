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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct run_softc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int RT2860_H2M_BUSY ; 
 int /*<<< orphan*/  RT2860_H2M_MAILBOX ; 
 int /*<<< orphan*/  RT2860_HOST_CMD ; 
 int RT2860_TOKEN_NO_INTR ; 
 int run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
run_mcu_cmd(struct run_softc *sc, uint8_t cmd, uint16_t arg)
{
	uint32_t tmp;
	int error, ntries;

	for (ntries = 0; ntries < 100; ntries++) {
		if ((error = run_read(sc, RT2860_H2M_MAILBOX, &tmp)) != 0)
			return error;
		if (!(tmp & RT2860_H2M_BUSY))
			break;
	}
	if (ntries == 100)
		return ETIMEDOUT;

	tmp = RT2860_H2M_BUSY | RT2860_TOKEN_NO_INTR << 16 | arg;
	if ((error = run_write(sc, RT2860_H2M_MAILBOX, tmp)) == 0)
		error = run_write(sc, RT2860_HOST_CMD, cmd);
	return (error);
}