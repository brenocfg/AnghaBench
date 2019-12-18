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
struct vmxnet3_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_CMD_GET_LINK ; 
 int vmxnet3_read_cmd (struct vmxnet3_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmxnet3_link_is_up(struct vmxnet3_softc *sc)
{
	uint32_t status;

	status = vmxnet3_read_cmd(sc, VMXNET3_CMD_GET_LINK);
	return !!(status & 0x1);
}