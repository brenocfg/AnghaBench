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
struct mac_mls {int mm_flags; int /*<<< orphan*/  mm_effective; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_MLS_FLAG_EFFECTIVE ; 

__attribute__((used)) static void
mls_copy_effective(struct mac_mls *labelfrom, struct mac_mls *labelto)
{

	KASSERT((labelfrom->mm_flags & MAC_MLS_FLAG_EFFECTIVE) != 0,
	    ("mls_copy_effective: labelfrom not effective"));

	labelto->mm_effective = labelfrom->mm_effective;
	labelto->mm_flags |= MAC_MLS_FLAG_EFFECTIVE;
}