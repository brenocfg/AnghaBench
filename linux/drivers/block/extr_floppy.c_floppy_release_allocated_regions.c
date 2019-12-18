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
struct io_region {int /*<<< orphan*/  size; scalar_t__ offset; } ;
struct TYPE_2__ {scalar_t__ address; } ;

/* Variables and functions */
 TYPE_1__* FDCS ; 
 struct io_region const* io_regions ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void floppy_release_allocated_regions(int fdc, const struct io_region *p)
{
	while (p != io_regions) {
		p--;
		release_region(FDCS->address + p->offset, p->size);
	}
}