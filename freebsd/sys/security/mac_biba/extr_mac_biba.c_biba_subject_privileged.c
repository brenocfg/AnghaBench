#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mbe_type; } ;
struct TYPE_6__ {scalar_t__ mbe_type; } ;
struct TYPE_4__ {scalar_t__ mbe_type; } ;
struct mac_biba {int mb_flags; TYPE_2__ mb_rangehigh; TYPE_3__ mb_rangelow; TYPE_1__ mb_effective; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_BIBA_FLAGS_BOTH ; 
 scalar_t__ MAC_BIBA_TYPE_EQUAL ; 
 scalar_t__ MAC_BIBA_TYPE_HIGH ; 
 scalar_t__ MAC_BIBA_TYPE_LOW ; 

__attribute__((used)) static int
biba_subject_privileged(struct mac_biba *mb)
{

	KASSERT((mb->mb_flags & MAC_BIBA_FLAGS_BOTH) == MAC_BIBA_FLAGS_BOTH,
	    ("biba_subject_privileged: subject doesn't have both labels"));

	/* If the effective is EQUAL, it's ok. */
	if (mb->mb_effective.mbe_type == MAC_BIBA_TYPE_EQUAL)
		return (0);

	/* If either range endpoint is EQUAL, it's ok. */
	if (mb->mb_rangelow.mbe_type == MAC_BIBA_TYPE_EQUAL ||
	    mb->mb_rangehigh.mbe_type == MAC_BIBA_TYPE_EQUAL)
		return (0);

	/* If the range is low-high, it's ok. */
	if (mb->mb_rangelow.mbe_type == MAC_BIBA_TYPE_LOW &&
	    mb->mb_rangehigh.mbe_type == MAC_BIBA_TYPE_HIGH)
		return (0);

	/* It's not ok. */
	return (EPERM);
}