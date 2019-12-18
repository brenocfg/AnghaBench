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
struct rad_handle {int /*<<< orphan*/  bindto; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */

void
rad_bind_to(struct rad_handle *h, in_addr_t addr)
{

	h->bindto = addr;
}