#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvlist_header {size_t nvlh_size; int /*<<< orphan*/  nvlh_descriptors; int /*<<< orphan*/  nvlh_flags; int /*<<< orphan*/  nvlh_version; int /*<<< orphan*/  nvlh_magic; } ;
struct TYPE_5__ {int /*<<< orphan*/  nvl_flags; } ;
typedef  TYPE_1__ nvlist_t ;
typedef  int /*<<< orphan*/  nvlhdr ;

/* Variables and functions */
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__ const*) ; 
 int /*<<< orphan*/  NVLIST_HEADER_MAGIC ; 
 int /*<<< orphan*/  NVLIST_HEADER_VERSION ; 
 int /*<<< orphan*/  NV_FLAG_BIG_ENDIAN ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,struct nvlist_header*,int) ; 
 int /*<<< orphan*/  nvlist_ndescriptors (TYPE_1__ const*) ; 

__attribute__((used)) static unsigned char *
nvlist_pack_header(const nvlist_t *nvl, unsigned char *ptr, size_t *leftp)
{
	struct nvlist_header nvlhdr;

	NVLIST_ASSERT(nvl);

	nvlhdr.nvlh_magic = NVLIST_HEADER_MAGIC;
	nvlhdr.nvlh_version = NVLIST_HEADER_VERSION;
	nvlhdr.nvlh_flags = nvl->nvl_flags;
#if BYTE_ORDER == BIG_ENDIAN
	nvlhdr.nvlh_flags |= NV_FLAG_BIG_ENDIAN;
#endif
	nvlhdr.nvlh_descriptors = nvlist_ndescriptors(nvl);
	nvlhdr.nvlh_size = *leftp - sizeof(nvlhdr);
	PJDLOG_ASSERT(*leftp >= sizeof(nvlhdr));
	memcpy(ptr, &nvlhdr, sizeof(nvlhdr));
	ptr += sizeof(nvlhdr);
	*leftp -= sizeof(nvlhdr);

	return (ptr);
}