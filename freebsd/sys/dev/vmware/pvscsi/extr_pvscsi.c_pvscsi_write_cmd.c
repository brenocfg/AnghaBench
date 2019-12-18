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
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_COMMAND ; 
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_COMMAND_DATA ; 
 int /*<<< orphan*/  pvscsi_reg_write (struct pvscsi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pvscsi_write_cmd(struct pvscsi_softc *sc, uint32_t cmd, void *data,
		 uint32_t len)
{
	uint32_t *data_ptr;
	int i;

	KASSERT(len % sizeof(uint32_t) == 0,
		("command size not a multiple of 4"));

	data_ptr = data;
	len /= sizeof(uint32_t);

	pvscsi_reg_write(sc, PVSCSI_REG_OFFSET_COMMAND, cmd);
	for (i = 0; i < len; ++i) {
		pvscsi_reg_write(sc, PVSCSI_REG_OFFSET_COMMAND_DATA,
		   data_ptr[i]);
	}
}