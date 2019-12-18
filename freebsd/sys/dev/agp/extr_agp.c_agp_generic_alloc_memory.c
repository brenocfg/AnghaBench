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
typedef  int vm_size_t ;
struct agp_softc {int as_maxmem; int as_allocated; int /*<<< orphan*/  as_memory; int /*<<< orphan*/  as_nextid; } ;
struct agp_memory {int am_size; scalar_t__ am_is_bound; scalar_t__ am_offset; scalar_t__ am_physical; int /*<<< orphan*/  am_obj; scalar_t__ am_type; scalar_t__ am_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AGP_PAGE_SIZE ; 
 int /*<<< orphan*/  M_AGP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OBJT_DEFAULT ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct agp_memory*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am_link ; 
 int /*<<< orphan*/  atop (int /*<<< orphan*/ ) ; 
 struct agp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct agp_memory* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  round_page (int) ; 
 int /*<<< orphan*/  vm_object_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct agp_memory *
agp_generic_alloc_memory(device_t dev, int type, vm_size_t size)
{
	struct agp_softc *sc = device_get_softc(dev);
	struct agp_memory *mem;

	if ((size & (AGP_PAGE_SIZE - 1)) != 0)
		return 0;

	if (size > sc->as_maxmem - sc->as_allocated)
		return 0;

	if (type != 0) {
		printf("agp_generic_alloc_memory: unsupported type %d\n",
		       type);
		return 0;
	}

	mem = malloc(sizeof *mem, M_AGP, M_WAITOK);
	mem->am_id = sc->as_nextid++;
	mem->am_size = size;
	mem->am_type = 0;
	mem->am_obj = vm_object_allocate(OBJT_DEFAULT, atop(round_page(size)));
	mem->am_physical = 0;
	mem->am_offset = 0;
	mem->am_is_bound = 0;
	TAILQ_INSERT_TAIL(&sc->as_memory, mem, am_link);
	sc->as_allocated += size;

	return mem;
}