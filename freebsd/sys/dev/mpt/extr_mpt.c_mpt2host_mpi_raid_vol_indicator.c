#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Low; int /*<<< orphan*/  High; } ;
struct TYPE_3__ {int /*<<< orphan*/  Low; int /*<<< orphan*/  High; } ;
typedef  int /*<<< orphan*/  MPI_RAID_VOL_INDICATOR ;

/* Variables and functions */
 TYPE_2__ BlocksRemaining ; 
 int /*<<< orphan*/  MPT_2_HOST16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ TotalBlocks ; 

void
mpt2host_mpi_raid_vol_indicator(MPI_RAID_VOL_INDICATOR *vi)
{

	MPT_2_HOST16(vi, TotalBlocks.High);
	MPT_2_HOST16(vi, TotalBlocks.Low);
	MPT_2_HOST16(vi, BlocksRemaining.High);
	MPT_2_HOST16(vi, BlocksRemaining.Low);
}