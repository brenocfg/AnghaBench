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
struct bcma_erom {int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */

__attribute__((used)) static void
bcma_erom_seek(struct bcma_erom *erom, bus_size_t offset)
{
	erom->offset = offset;
}