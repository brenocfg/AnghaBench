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
struct nvpair_header {size_t nvph_namesize; int /*<<< orphan*/  nvph_nitems; int /*<<< orphan*/  nvph_datasize; int /*<<< orphan*/  nvph_type; } ;
typedef  int /*<<< orphan*/  nvphdr ;
struct TYPE_4__ {struct nvpair_header* nvp_name; int /*<<< orphan*/  nvp_nitems; int /*<<< orphan*/  nvp_datasize; int /*<<< orphan*/  nvp_type; } ;
typedef  TYPE_1__ nvpair_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR_ASSERT (TYPE_1__ const*) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 size_t UINT16_MAX ; 
 int /*<<< orphan*/  memcpy (unsigned char*,struct nvpair_header*,size_t) ; 
 int strlen (struct nvpair_header*) ; 

unsigned char *
nvpair_pack_header(const nvpair_t *nvp, unsigned char *ptr, size_t *leftp)
{
	struct nvpair_header nvphdr;
	size_t namesize;

	NVPAIR_ASSERT(nvp);

	nvphdr.nvph_type = nvp->nvp_type;
	namesize = strlen(nvp->nvp_name) + 1;
	PJDLOG_ASSERT(namesize > 0 && namesize <= UINT16_MAX);
	nvphdr.nvph_namesize = namesize;
	nvphdr.nvph_datasize = nvp->nvp_datasize;
	nvphdr.nvph_nitems = nvp->nvp_nitems;
	PJDLOG_ASSERT(*leftp >= sizeof(nvphdr));
	memcpy(ptr, &nvphdr, sizeof(nvphdr));
	ptr += sizeof(nvphdr);
	*leftp -= sizeof(nvphdr);

	PJDLOG_ASSERT(*leftp >= namesize);
	memcpy(ptr, nvp->nvp_name, namesize);
	ptr += namesize;
	*leftp -= namesize;

	return (ptr);
}