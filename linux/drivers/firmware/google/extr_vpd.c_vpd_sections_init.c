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
struct vpd_cbmem {scalar_t__ magic; scalar_t__ rw_size; scalar_t__ ro_size; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MEMREMAP_WB ; 
 scalar_t__ VPD_CBMEM_MAGIC ; 
 int /*<<< orphan*/  memcpy (struct vpd_cbmem*,struct vpd_cbmem*,int) ; 
 struct vpd_cbmem* memremap (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memunmap (struct vpd_cbmem*) ; 
 int /*<<< orphan*/  ro_vpd ; 
 int /*<<< orphan*/  rw_vpd ; 
 int /*<<< orphan*/  vpd_section_destroy (int /*<<< orphan*/ *) ; 
 int vpd_section_init (char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int vpd_sections_init(phys_addr_t physaddr)
{
	struct vpd_cbmem *temp;
	struct vpd_cbmem header;
	int ret = 0;

	temp = memremap(physaddr, sizeof(struct vpd_cbmem), MEMREMAP_WB);
	if (!temp)
		return -ENOMEM;

	memcpy(&header, temp, sizeof(struct vpd_cbmem));
	memunmap(temp);

	if (header.magic != VPD_CBMEM_MAGIC)
		return -ENODEV;

	if (header.ro_size) {
		ret = vpd_section_init("ro", &ro_vpd,
				       physaddr + sizeof(struct vpd_cbmem),
				       header.ro_size);
		if (ret)
			return ret;
	}

	if (header.rw_size) {
		ret = vpd_section_init("rw", &rw_vpd,
				       physaddr + sizeof(struct vpd_cbmem) +
				       header.ro_size, header.rw_size);
		if (ret) {
			vpd_section_destroy(&ro_vpd);
			return ret;
		}
	}

	return 0;
}