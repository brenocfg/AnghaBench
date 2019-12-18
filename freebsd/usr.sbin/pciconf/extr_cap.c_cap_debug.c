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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct pci_conf {int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
 int PCIM_DEBUG_PORT_OFFSET ; 
 int PCIR_BAR (int) ; 
 scalar_t__ PCIR_DEBUG_PORT ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int read_config (int,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void
cap_debug(int fd, struct pci_conf *p, uint8_t ptr)
{
	uint16_t debug_port;

	debug_port = read_config(fd, &p->pc_sel, ptr + PCIR_DEBUG_PORT, 2);
	printf("EHCI Debug Port at offset 0x%x in map 0x%x", debug_port &
	    PCIM_DEBUG_PORT_OFFSET, PCIR_BAR(debug_port >> 13));
}