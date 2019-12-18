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
struct mac_mls {int mm_flags; } ;

/* Variables and functions */
 int MAC_MLS_FLAG_EFFECTIVE ; 
 int MAC_MLS_FLAG_RANGE ; 
 int /*<<< orphan*/  mls_copy_effective (struct mac_mls*,struct mac_mls*) ; 
 int /*<<< orphan*/  mls_copy_range (struct mac_mls*,struct mac_mls*) ; 

__attribute__((used)) static void
mls_copy(struct mac_mls *source, struct mac_mls *dest)
{

	if (source->mm_flags & MAC_MLS_FLAG_EFFECTIVE)
		mls_copy_effective(source, dest);
	if (source->mm_flags & MAC_MLS_FLAG_RANGE)
		mls_copy_range(source, dest);
}