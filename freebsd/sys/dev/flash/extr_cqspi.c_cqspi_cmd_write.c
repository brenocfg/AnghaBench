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
struct cqspi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQSPI_FLASHCMD ; 
 int FLASHCMD_CMDOPCODE_S ; 
 int FLASHCMD_EXECCMD ; 
 int /*<<< orphan*/  WRITE4 (struct cqspi_softc*,int /*<<< orphan*/ ,int) ; 
 int cqspi_wait_for_completion (struct cqspi_softc*) ; 

__attribute__((used)) static int
cqspi_cmd_write(struct cqspi_softc *sc, uint8_t cmd,
    uint8_t *addr, uint32_t len)
{
	uint32_t reg;
	int ret;

	reg = (cmd << FLASHCMD_CMDOPCODE_S);
	WRITE4(sc, CQSPI_FLASHCMD, reg);
	reg |= FLASHCMD_EXECCMD;
	WRITE4(sc, CQSPI_FLASHCMD, reg);

	ret = cqspi_wait_for_completion(sc);

	return (ret);
}