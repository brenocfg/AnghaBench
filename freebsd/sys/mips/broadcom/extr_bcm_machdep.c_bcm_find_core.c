#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct bhnd_core_match {int dummy; } ;
struct bhnd_core_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;
struct bcm_platform {TYPE_1__ erom; } ;
typedef  int /*<<< orphan*/  bhnd_size_t ;
typedef  uintptr_t bhnd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PORT_DEVICE ; 
 int ENOENT ; 
 int ERANGE ; 
 uintptr_t UINTPTR_MAX ; 
 int bhnd_erom_lookup_core_addr (int /*<<< orphan*/ *,struct bhnd_core_match const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhnd_core_info*,uintptr_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bcm_find_core(struct bcm_platform *bp, const struct bhnd_core_match *descs,
    size_t num_descs, struct bhnd_core_info *info, uintptr_t *addr)
{
	bhnd_addr_t		b_addr;
	bhnd_size_t		b_size;
	int			error;

	/* Fetch core info */
	for (size_t i = 0; i < num_descs; i++) {
		error = bhnd_erom_lookup_core_addr(&bp->erom.obj, &descs[i],
		    BHND_PORT_DEVICE, 0, 0, info, &b_addr, &b_size);

		/* Terminate search on first match */
		if (error == 0)
			break;

		/* Terminate on first error (other than core not found) */
		if (error != ENOENT)
			return (error);

		/* Continue search ... */
	}

	/* Provide the core's base address */
	if (addr != NULL && b_addr > UINTPTR_MAX) {
		BCM_ERR("core address %#jx overflows native address width\n",
		    (uintmax_t)b_addr);
		return (ERANGE);
	}

	if (addr != NULL)
		*addr = b_addr;

	return (0);
}