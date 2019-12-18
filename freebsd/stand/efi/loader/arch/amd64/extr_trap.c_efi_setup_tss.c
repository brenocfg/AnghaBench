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
struct system_segment_descriptor {int sd_lolimit; int sd_lobase; int sd_p; int sd_hilimit; int sd_hibase; scalar_t__ sd_xx2; scalar_t__ sd_mbz; scalar_t__ sd_xx1; scalar_t__ sd_xx0; scalar_t__ sd_gran; scalar_t__ sd_dpl; int /*<<< orphan*/  sd_type; } ;
struct region_descriptor {scalar_t__ rd_base; } ;
struct amd64tss {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* AllocatePages ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateAnyPages ; 
 TYPE_1__* BS ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFI_ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFI_SIZE_TO_PAGES (int) ; 
 int /*<<< orphan*/  EfiLoaderData ; 
 int /*<<< orphan*/  SDT_SYSTSS ; 
 int /*<<< orphan*/  bzero (struct amd64tss*,int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int tss_pa ; 

__attribute__((used)) static int
efi_setup_tss(struct region_descriptor *gdt, uint32_t loader_tss_idx,
    struct amd64tss **tss)
{
	EFI_STATUS status;
	struct system_segment_descriptor *tss_desc;

	tss_desc = (struct system_segment_descriptor *)(gdt->rd_base +
	    (loader_tss_idx << 3));
	status = BS->AllocatePages(AllocateAnyPages, EfiLoaderData,
	    EFI_SIZE_TO_PAGES(sizeof(struct amd64tss)), &tss_pa);
	if (EFI_ERROR(status)) {
		printf("efi_setup_tss: AllocatePages tss error %lu\n",
		    EFI_ERROR_CODE(status));
		return (0);
	}
	*tss = (struct amd64tss *)tss_pa;
	bzero(*tss, sizeof(**tss));
	tss_desc->sd_lolimit = sizeof(struct amd64tss);
	tss_desc->sd_lobase = tss_pa;
	tss_desc->sd_type = SDT_SYSTSS;
	tss_desc->sd_dpl = 0;
	tss_desc->sd_p = 1;
	tss_desc->sd_hilimit = sizeof(struct amd64tss) >> 16;
	tss_desc->sd_gran = 0;
	tss_desc->sd_hibase = tss_pa >> 24;
	tss_desc->sd_xx0 = 0;
	tss_desc->sd_xx1 = 0;
	tss_desc->sd_mbz = 0;
	tss_desc->sd_xx2 = 0;
	return (1);
}