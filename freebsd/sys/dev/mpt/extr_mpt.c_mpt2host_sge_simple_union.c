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
struct TYPE_3__ {int /*<<< orphan*/  High; int /*<<< orphan*/  Low; } ;
struct TYPE_4__ {TYPE_1__ Address64; } ;
typedef  int /*<<< orphan*/  SGE_SIMPLE_UNION ;

/* Variables and functions */
 int /*<<< orphan*/  FlagsLength ; 
 int /*<<< orphan*/  MPT_2_HOST32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ u ; 

void
mpt2host_sge_simple_union(SGE_SIMPLE_UNION *sge)
{

	MPT_2_HOST32(sge, FlagsLength);
	MPT_2_HOST32(sge, u.Address64.Low);
	MPT_2_HOST32(sge, u.Address64.High);
}