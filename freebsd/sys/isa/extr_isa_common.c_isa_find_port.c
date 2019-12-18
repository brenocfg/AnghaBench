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
typedef  int uint32_t ;
struct resource {int dummy; } ;
struct isa_config {int ic_nport; TYPE_1__* ic_port; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int ir_size; int ir_start; int ir_end; int ir_align; } ;

/* Variables and functions */
 int ISA_NPORT ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  rman_make_alignment_flags (int) ; 

__attribute__((used)) static int
isa_find_port(device_t child, struct isa_config *config,
    struct isa_config *result)
{
	int success, i;
	struct resource *res[ISA_NPORT];

	/*
	 * First clear out any existing resource definitions.
	 */
	for (i = 0; i < ISA_NPORT; i++) {
		bus_delete_resource(child, SYS_RES_IOPORT, i);
		res[i] = NULL;
	}

	success = 1;
	result->ic_nport = config->ic_nport;
	for (i = 0; i < config->ic_nport; i++) {
		uint32_t start, end, size, align;

		size = config->ic_port[i].ir_size;

		/* the PnP device may have a null resource as filler */
		if (size == 0) {
			result->ic_port[i].ir_start = 0;
			result->ic_port[i].ir_end = 0;
			result->ic_port[i].ir_size = 0;
			result->ic_port[i].ir_align = 0;
			continue;
		}

		for (start = config->ic_port[i].ir_start,
			     end = config->ic_port[i].ir_end,
			     align = config->ic_port[i].ir_align;
		     start + size - 1 <= end;
		     start += align) {
			bus_set_resource(child, SYS_RES_IOPORT, i,
					 start, size);
			res[i] = bus_alloc_resource_any(child,
			    SYS_RES_IOPORT, &i,
			    rman_make_alignment_flags(align) /* !RF_ACTIVE */);
			if (res[i]) {
				result->ic_port[i].ir_start = start;
				result->ic_port[i].ir_end = start + size - 1;
				result->ic_port[i].ir_size = size;
				result->ic_port[i].ir_align = align;
				break;
			}
		}

		/*
		 * If we didn't find a place for port range i, then 
		 * give up now.
		 */
		if (!res[i]) {
			success = 0;
			break;
		}
	}

	for (i = 0; i < ISA_NPORT; i++) {
		if (res[i])
			bus_release_resource(child, SYS_RES_IOPORT,
					     i, res[i]);
	}

	return success;
}