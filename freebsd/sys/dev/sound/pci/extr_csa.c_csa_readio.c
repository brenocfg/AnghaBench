#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int u_int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  io; } ;
typedef  TYPE_1__ csa_res ;

/* Variables and functions */
 scalar_t__ BA0_AC97_RESET ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ csa_readcodec (TYPE_1__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

u_int32_t
csa_readio(csa_res *resp, u_long offset)
{
	u_int32_t ul;

	if (offset < BA0_AC97_RESET)
		return bus_space_read_4(rman_get_bustag(resp->io), rman_get_bushandle(resp->io), offset) & 0xffffffff;
	else {
		if (csa_readcodec(resp, offset, &ul))
			ul = 0;
		return (ul);
	}
}