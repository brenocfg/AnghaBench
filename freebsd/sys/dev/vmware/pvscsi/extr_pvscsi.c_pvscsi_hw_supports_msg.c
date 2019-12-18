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
typedef  int uint32_t ;
struct pvscsi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_CMD_SETUP_MSG_RING ; 
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_COMMAND ; 
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_COMMAND_STATUS ; 
 int pvscsi_reg_read (struct pvscsi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_reg_write (struct pvscsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pvscsi_hw_supports_msg(struct pvscsi_softc *sc)
{
	uint32_t status;

	pvscsi_reg_write(sc, PVSCSI_REG_OFFSET_COMMAND,
	    PVSCSI_CMD_SETUP_MSG_RING);
	status = pvscsi_reg_read(sc, PVSCSI_REG_OFFSET_COMMAND_STATUS);

	return (status != -1);
}