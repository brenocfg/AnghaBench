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
struct vmxnet3_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_CMD_GET_STATS ; 
 int /*<<< orphan*/  vmxnet3_write_cmd (struct vmxnet3_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_refresh_host_stats(struct vmxnet3_softc *sc)
{

	vmxnet3_write_cmd(sc, VMXNET3_CMD_GET_STATS);
}