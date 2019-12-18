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
typedef  int uintmax_t ;
typedef  int u_int ;
struct bhnd_resource {int /*<<< orphan*/  res; } ;
struct bhnd_nvram_io {int /*<<< orphan*/ * iops; } ;
struct bhnd_nvram_iores {int bus_width; struct bhnd_nvram_io io; scalar_t__ size; scalar_t__ offset; struct bhnd_resource* res; } ;
typedef  scalar_t__ rman_res_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_LOG (char*,int,...) ; 
 scalar_t__ BUS_SPACE_MAXSIZE ; 
 int /*<<< orphan*/  M_BHND_NVRAM ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  bhnd_nvram_iores_ops ; 
 struct bhnd_nvram_iores* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_size (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 

struct bhnd_nvram_io *
bhnd_nvram_iores_new(struct bhnd_resource *r, bus_size_t offset,
    bus_size_t size, u_int bus_width)
{
	struct bhnd_nvram_iores	*iores;
	rman_res_t		 r_start, r_size;

	/* Verify the bus width */
	switch (bus_width) {
	case 1:
	case 2:
	case 4:
		/* valid */
		break;
	default:
		BHND_NV_LOG("invalid bus width %u\n", bus_width);
		return (NULL);
	}

	/* offset/size must not exceed our internal size_t representation,
	 * or our bus_size_t usage (note that BUS_SPACE_MAXSIZE may be less
	 * than 2^(sizeof(bus_size_t) * 32). */
	if (size > SIZE_MAX || offset > SIZE_MAX) {
		BHND_NV_LOG("offset %#jx+%#jx exceeds SIZE_MAX\n",
		    (uintmax_t)offset, (uintmax_t)offset);
		return (NULL);
	}
	
	if (size > BUS_SPACE_MAXSIZE || offset > BUS_SPACE_MAXSIZE)
	{
		BHND_NV_LOG("offset %#jx+%#jx exceeds BUS_SPACE_MAXSIZE\n",
		    (uintmax_t)offset, (uintmax_t)offset);
		return (NULL);
	}

	/* offset/size fall within the resource's mapped range */
	r_size = rman_get_size(r->res);
	r_start = rman_get_start(r->res);
	if (r_size < offset || r_size < size || r_size - size < offset)
		return (NULL);

	/* offset/size must be bus_width aligned  */
	if ((r_start + offset) % bus_width != 0) {
		BHND_NV_LOG("base address %#jx+%#jx not aligned to bus width "
		    "%u\n", (uintmax_t)r_start, (uintmax_t)offset, bus_width);
		return (NULL);
	}

	if (size % bus_width != 0) {
		BHND_NV_LOG("size %#jx not aligned to bus width %u\n",
		    (uintmax_t)size, bus_width);
		return (NULL);
	}

	/* Allocate and return the I/O context */
	iores = malloc(sizeof(*iores), M_BHND_NVRAM, M_WAITOK);
	iores->io.iops = &bhnd_nvram_iores_ops;
	iores->res = r;
	iores->offset = offset;
	iores->size = size;
	iores->bus_width = bus_width;

	return (&iores->io);
}