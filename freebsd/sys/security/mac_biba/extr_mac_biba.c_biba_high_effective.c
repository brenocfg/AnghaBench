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
struct TYPE_2__ {scalar_t__ mbe_type; } ;
struct mac_biba {int mb_flags; TYPE_1__ mb_effective; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_BIBA_FLAG_EFFECTIVE ; 
 scalar_t__ MAC_BIBA_TYPE_HIGH ; 

__attribute__((used)) static int
biba_high_effective(struct mac_biba *mb)
{

	KASSERT((mb->mb_flags & MAC_BIBA_FLAG_EFFECTIVE) != 0,
	    ("biba_equal_effective: mb not effective"));

	return (mb->mb_effective.mbe_type == MAC_BIBA_TYPE_HIGH);
}