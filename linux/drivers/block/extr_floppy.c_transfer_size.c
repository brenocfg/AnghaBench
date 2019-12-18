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
struct TYPE_2__ {int sect; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUPBOUND (int,scalar_t__) ; 
 TYPE_1__* _floppy ; 
 scalar_t__ current_count_sectors ; 
 scalar_t__ fsector_t ; 

__attribute__((used)) static int transfer_size(int ssize, int max_sector, int max_size)
{
	SUPBOUND(max_sector, fsector_t + max_size);

	/* alignment */
	max_sector -= (max_sector % _floppy->sect) % ssize;

	/* transfer size, beginning not aligned */
	current_count_sectors = max_sector - fsector_t;

	return max_sector;
}