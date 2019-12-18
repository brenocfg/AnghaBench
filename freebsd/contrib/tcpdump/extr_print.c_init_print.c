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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  init_addrtoname (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_checksum () ; 
 int /*<<< orphan*/  thiszone ; 

void
init_print(netdissect_options *ndo, uint32_t localnet, uint32_t mask,
    uint32_t timezone_offset)
{

	thiszone = timezone_offset;
	init_addrtoname(ndo, localnet, mask);
	init_checksum();
}