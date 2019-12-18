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
typedef  uintptr_t vm_offset_t ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  emergency_buffer ;
typedef  int cell_t ;

/* Variables and functions */
 uintptr_t DMAP_BASE_ADDRESS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_bounce_mtx ; 
 int of_bounce_offset ; 
 int of_bounce_phys ; 
 int of_bounce_size ; 
 char* of_bounce_virt ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_bootstrapped ; 

__attribute__((used)) static cell_t
ofw_real_map(const void *buf, size_t len)
{
	static char emergency_buffer[255];
	cell_t phys;

	mtx_assert(&of_bounce_mtx, MA_OWNED);

	if (of_bounce_virt == NULL) {
		/*
		 * If we haven't set up the MMU, then buf is guaranteed
		 * to be accessible to OF, because the only memory we
		 * can use right now is memory mapped by firmware.
		 */
		if (!pmap_bootstrapped)
			return (cell_t)((uintptr_t)buf & ~DMAP_BASE_ADDRESS);

		/*
		 * XXX: It is possible for us to get called before the VM has
		 * come online, but after the MMU is up. We don't have the
		 * bounce buffer yet, but can no longer presume a 1:1 mapping.
		 * Copy into the emergency buffer, and reset at the end.
		 */
		of_bounce_virt = emergency_buffer;
		of_bounce_phys = (vm_offset_t)of_bounce_virt &
		    ~DMAP_BASE_ADDRESS;
		of_bounce_size = sizeof(emergency_buffer);
	}

	/*
	 * Make sure the bounce page offset satisfies any reasonable
	 * alignment constraint.
	 */
	of_bounce_offset += sizeof(register_t) -
	    (of_bounce_offset % sizeof(register_t));

	if (of_bounce_offset + len > of_bounce_size) {
		panic("Oversize Open Firmware call!");
		return 0;
	}

	if (buf != NULL)
		memcpy(of_bounce_virt + of_bounce_offset, buf, len);
	else
		return (0);

	phys = of_bounce_phys + of_bounce_offset;

	of_bounce_offset += len;

	return (phys);
}