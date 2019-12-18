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
typedef  int /*<<< orphan*/  register_t ;
typedef  scalar_t__ cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int rtas_bounce_offset ; 
 scalar_t__ rtas_bounce_phys ; 
 int rtas_bounce_size ; 
 scalar_t__ rtas_bounce_virt ; 
 int /*<<< orphan*/  rtas_mtx ; 

__attribute__((used)) static cell_t
rtas_real_map(const void *buf, size_t len)
{
	cell_t phys;

	mtx_assert(&rtas_mtx, MA_OWNED);

	/*
	 * Make sure the bounce page offset satisfies any reasonable
	 * alignment constraint.
	 */
	rtas_bounce_offset += sizeof(register_t) -
	    (rtas_bounce_offset % sizeof(register_t));

	if (rtas_bounce_offset + len > rtas_bounce_size) {
		panic("Oversize RTAS call!");
		return 0;
	}

	if (buf != NULL)
		memcpy(rtas_bounce_virt + rtas_bounce_offset, buf, len);
	else
		return (0);

	phys = rtas_bounce_phys + rtas_bounce_offset;
	rtas_bounce_offset += len;

	return (phys);
}