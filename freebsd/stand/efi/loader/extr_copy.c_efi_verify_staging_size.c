#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int UINTN ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_9__ {int /*<<< orphan*/  (* GetMemoryMap ) (int*,TYPE_1__*,int*,int*,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {scalar_t__ PhysicalStart; int NumberOfPages; scalar_t__ Type; } ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  scalar_t__ EFI_PHYSICAL_ADDRESS ;
typedef  TYPE_1__ EFI_MEMORY_DESCRIPTOR ;

/* Variables and functions */
 TYPE_7__* BS ; 
 int /*<<< orphan*/  EFI_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  EFI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFI_ERROR_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ EFI_PAGE_SHIFT ; 
 int EFI_PAGE_SIZE ; 
 scalar_t__ EfiConventionalMemory ; 
 scalar_t__ EfiLoaderData ; 
 scalar_t__ KERNEL_PHYSICAL_BASE ; 
 TYPE_1__* NextMemoryDescriptor (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (int*,TYPE_1__*,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
efi_verify_staging_size(unsigned long *nr_pages)
{
	UINTN sz;
	EFI_MEMORY_DESCRIPTOR *map = NULL, *p;
	EFI_PHYSICAL_ADDRESS start, end;
	UINTN key, dsz;
	UINT32 dver;
	EFI_STATUS status;
	int i, ndesc;
	unsigned long available_pages = 0;

	sz = 0;

	for (;;) {
		status = BS->GetMemoryMap(&sz, map, &key, &dsz, &dver);
		if (!EFI_ERROR(status))
			break;

		if (status != EFI_BUFFER_TOO_SMALL) {
			printf("Can't read memory map: %lu\n",
			    EFI_ERROR_CODE(status));
			goto out;
		}

		free(map);

		/* Allocate 10 descriptors more than the size reported,
		 * to allow for any fragmentation caused by calling
		 * malloc */
		map = malloc(sz + (10 * dsz));
		if (map == NULL) {
			printf("Unable to allocate memory\n");
			goto out;
		}
	}

	ndesc = sz / dsz;
	for (i = 0, p = map; i < ndesc;
	     i++, p = NextMemoryDescriptor(p, dsz)) {
		start = p->PhysicalStart;
		end = start + p->NumberOfPages * EFI_PAGE_SIZE;

		if (KERNEL_PHYSICAL_BASE < start ||
		    KERNEL_PHYSICAL_BASE >= end)
			continue;

		available_pages = p->NumberOfPages -
			((KERNEL_PHYSICAL_BASE - start) >> EFI_PAGE_SHIFT);
		break;
	}

	if (available_pages == 0) {
		printf("Can't find valid memory map for staging area!\n");
		goto out;
	}

	i++;
	p = NextMemoryDescriptor(p, dsz);

	for ( ; i < ndesc;
	     i++, p = NextMemoryDescriptor(p, dsz)) {
		if (p->Type != EfiConventionalMemory &&
		    p->Type != EfiLoaderData)
			break;

		if (p->PhysicalStart != end)
			break;

		end = p->PhysicalStart + p->NumberOfPages * EFI_PAGE_SIZE;

		available_pages += p->NumberOfPages;
	}

	if (*nr_pages > available_pages) {
		printf("Staging area's size is reduced: %ld -> %ld!\n",
		    *nr_pages, available_pages);
		*nr_pages = available_pages;
	}
out:
	free(map);
}