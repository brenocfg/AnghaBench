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
typedef  scalar_t__ uint32_t ;
struct fdt_property {void* nameoff; } ;
typedef  void* fdt32_t ;

/* Variables and functions */
 scalar_t__ FDT_END ; 
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  FDT_MAGIC ; 
 scalar_t__ FDT_PROP ; 
 int /*<<< orphan*/  FDT_SW_CHECK_HEADER (void*) ; 
 void* cpu_to_fdt32 (int) ; 
 int fdt32_to_cpu (void*) ; 
 void** fdt_grab_space_ (void*,int) ; 
 scalar_t__ fdt_next_tag (void*,int,int*) ; 
 int fdt_off_dt_struct (void*) ; 
 struct fdt_property* fdt_offset_ptr_w_ (void*,int) ; 
 int /*<<< orphan*/  fdt_set_magic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_off_dt_strings (void*,int) ; 
 int /*<<< orphan*/  fdt_set_totalsize (void*,int) ; 
 int fdt_size_dt_strings (void*) ; 
 int fdt_size_dt_struct (void*) ; 
 int fdt_totalsize (void*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

int fdt_finish(void *fdt)
{
	char *p = (char *)fdt;
	fdt32_t *end;
	int oldstroffset, newstroffset;
	uint32_t tag;
	int offset, nextoffset;

	FDT_SW_CHECK_HEADER(fdt);

	/* Add terminator */
	end = fdt_grab_space_(fdt, sizeof(*end));
	if (! end)
		return -FDT_ERR_NOSPACE;
	*end = cpu_to_fdt32(FDT_END);

	/* Relocate the string table */
	oldstroffset = fdt_totalsize(fdt) - fdt_size_dt_strings(fdt);
	newstroffset = fdt_off_dt_struct(fdt) + fdt_size_dt_struct(fdt);
	memmove(p + newstroffset, p + oldstroffset, fdt_size_dt_strings(fdt));
	fdt_set_off_dt_strings(fdt, newstroffset);

	/* Walk the structure, correcting string offsets */
	offset = 0;
	while ((tag = fdt_next_tag(fdt, offset, &nextoffset)) != FDT_END) {
		if (tag == FDT_PROP) {
			struct fdt_property *prop =
				fdt_offset_ptr_w_(fdt, offset);
			int nameoff;

			nameoff = fdt32_to_cpu(prop->nameoff);
			nameoff += fdt_size_dt_strings(fdt);
			prop->nameoff = cpu_to_fdt32(nameoff);
		}
		offset = nextoffset;
	}
	if (nextoffset < 0)
		return nextoffset;

	/* Finally, adjust the header */
	fdt_set_totalsize(fdt, newstroffset + fdt_size_dt_strings(fdt));
	fdt_set_magic(fdt, FDT_MAGIC);
	return 0;
}