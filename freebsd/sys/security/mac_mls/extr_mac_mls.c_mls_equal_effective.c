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
 int mls_equal_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mls_equal_effective(struct mac_mls *a, struct mac_mls *b)
{

	KASSERT((a->mm_flags & MAC_MLS_FLAG_EFFECTIVE) != 0,
	    ("mls_equal_effective: a not effective"));
	KASSERT((b->mm_flags & MAC_MLS_FLAG_EFFECTIVE) != 0,
	    ("mls_equal_effective: b not effective"));

	return (mls_equal_element(&a->mm_effective, &b->mm_effective));
}