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
typedef  int /*<<< orphan*/  vmci_io_port ;
typedef  int /*<<< orphan*/  vmci_io_handle ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  insb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

void
vmci_read_port_bytes(vmci_io_handle handle, vmci_io_port port, uint8_t *buffer,
    size_t buffer_length)
{

	insb(port, buffer, buffer_length);
}