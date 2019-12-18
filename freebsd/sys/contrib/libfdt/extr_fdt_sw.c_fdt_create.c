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
struct fdt_reserve_entry {int dummy; } ;
struct fdt_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_ALIGN (int,int) ; 
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  FDT_FIRST_SUPPORTED_VERSION ; 
 int /*<<< orphan*/  FDT_LAST_SUPPORTED_VERSION ; 
 int /*<<< orphan*/  FDT_SW_MAGIC ; 
 int /*<<< orphan*/  fdt_off_mem_rsvmap (void*) ; 
 int /*<<< orphan*/  fdt_set_last_comp_version (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_magic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_off_dt_strings (void*,int) ; 
 int /*<<< orphan*/  fdt_set_off_dt_struct (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_off_mem_rsvmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_totalsize (void*,int) ; 
 int /*<<< orphan*/  fdt_set_version (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

int fdt_create(void *buf, int bufsize)
{
	void *fdt = buf;

	if (bufsize < sizeof(struct fdt_header))
		return -FDT_ERR_NOSPACE;

	memset(buf, 0, bufsize);

	fdt_set_magic(fdt, FDT_SW_MAGIC);
	fdt_set_version(fdt, FDT_LAST_SUPPORTED_VERSION);
	fdt_set_last_comp_version(fdt, FDT_FIRST_SUPPORTED_VERSION);
	fdt_set_totalsize(fdt,  bufsize);

	fdt_set_off_mem_rsvmap(fdt, FDT_ALIGN(sizeof(struct fdt_header),
					      sizeof(struct fdt_reserve_entry)));
	fdt_set_off_dt_struct(fdt, fdt_off_mem_rsvmap(fdt));
	fdt_set_off_dt_strings(fdt, bufsize);

	return 0;
}