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
struct run_softc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  RT2860_BBP_CSR_CFG ; 
 int RT2860_BBP_CSR_KICK ; 
 int run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
run_bbp_write(struct run_softc *sc, uint8_t reg, uint8_t val)
{
	uint32_t tmp;
	int ntries, error;

	for (ntries = 0; ntries < 10; ntries++) {
		if ((error = run_read(sc, RT2860_BBP_CSR_CFG, &tmp)) != 0)
			return (error);
		if (!(tmp & RT2860_BBP_CSR_KICK))
			break;
	}
	if (ntries == 10)
		return (ETIMEDOUT);

	tmp = RT2860_BBP_CSR_KICK | reg << 8 | val;
	return (run_write(sc, RT2860_BBP_CSR_CFG, tmp));
}