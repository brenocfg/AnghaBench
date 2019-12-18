#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ocs_hw_t ;
struct TYPE_3__ {int /*<<< orphan*/  is_port_owned; } ;
typedef  TYPE_1__ ocs_hw_io_t ;

/* Variables and functions */

uint8_t
ocs_hw_is_io_port_owned(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	/* Check to see if this is a port owned XRI */
	return io->is_port_owned;
}