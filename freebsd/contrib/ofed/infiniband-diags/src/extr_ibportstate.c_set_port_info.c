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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBEXIT (char*) ; 
 int /*<<< orphan*/  IB_ATTR_PORT_INFO ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  show_port_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  smp_set_via (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 

__attribute__((used)) static void set_port_info(ib_portid_t * dest, uint8_t * data, int portnum,
			  int espeed_cap, int is_switch)
{
	unsigned mod;

	mod = portnum;
	if (espeed_cap)
		mod |= 1<<31;
	if (!smp_set_via(data, dest, IB_ATTR_PORT_INFO, mod, 0, srcport))
		IBEXIT("smp set portinfo failed");

	printf("\nAfter PortInfo set:\n");
	show_port_info(dest, data, portnum, espeed_cap, is_switch);
}