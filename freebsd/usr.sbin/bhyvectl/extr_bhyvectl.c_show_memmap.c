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
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
struct vmctx {int dummy; } ;
typedef  int /*<<< orphan*/  numbuf ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int /*<<< orphan*/  HN_NOSPACE ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SPECNAMELEN ; 
 int VM_MEMMAP_F_IOMMU ; 
 int VM_MEMMAP_F_WIRED ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  humanize_number (char*,int,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int vm_get_memseg (struct vmctx*,int,size_t*,char*,int) ; 
 int vm_mmap_getnext (struct vmctx*,scalar_t__*,int*,int /*<<< orphan*/ *,size_t*,int*,int*) ; 

__attribute__((used)) static int
show_memmap(struct vmctx *ctx)
{
	char name[SPECNAMELEN + 1], numbuf[8];
	vm_ooffset_t segoff;
	vm_paddr_t gpa;
	size_t maplen, seglen;
	int error, flags, prot, segid, delim;

	printf("Address     Length      Segment     Offset      ");
	printf("Prot  Flags\n");

	gpa = 0;
	while (1) {
		error = vm_mmap_getnext(ctx, &gpa, &segid, &segoff, &maplen,
		    &prot, &flags);
		if (error)
			return (errno == ENOENT ? 0 : error);

		error = vm_get_memseg(ctx, segid, &seglen, name, sizeof(name));
		if (error)
			return (error);

		printf("%-12lX", gpa);
		humanize_number(numbuf, sizeof(numbuf), maplen, "B",
		    HN_AUTOSCALE, HN_NOSPACE);
		printf("%-12s", numbuf);

		printf("%-12s", name[0] ? name : "sysmem");
		printf("%-12lX", segoff);
		printf("%c%c%c   ", prot & PROT_READ ? 'R' : '-',
		    prot & PROT_WRITE ? 'W' : '-',
		    prot & PROT_EXEC ? 'X' : '-');

		delim = '\0';
		if (flags & VM_MEMMAP_F_WIRED) {
			printf("%cwired", delim);
			delim = '/';
		}
		if (flags & VM_MEMMAP_F_IOMMU) {
			printf("%ciommu", delim);
			delim = '/';
		}
		printf("\n");

		gpa += maplen;
	}
}