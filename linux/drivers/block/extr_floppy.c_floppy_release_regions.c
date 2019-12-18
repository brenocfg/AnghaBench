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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floppy_release_allocated_regions (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_regions ; 

__attribute__((used)) static void floppy_release_regions(int fdc)
{
	floppy_release_allocated_regions(fdc, ARRAY_END(io_regions));
}