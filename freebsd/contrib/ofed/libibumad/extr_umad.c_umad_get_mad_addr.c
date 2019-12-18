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
struct ib_user_mad {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  ib_mad_addr_t ;

/* Variables and functions */

ib_mad_addr_t *umad_get_mad_addr(void *umad)
{
	struct ib_user_mad *mad = umad;

	return &mad->addr;
}