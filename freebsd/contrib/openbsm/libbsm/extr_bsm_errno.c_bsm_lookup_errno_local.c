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
struct bsm_errno {int be_local_errno; } ;

/* Variables and functions */
 struct bsm_errno const* bsm_errnos ; 
 int bsm_errnos_count ; 

__attribute__((used)) static const struct bsm_errno *
bsm_lookup_errno_local(int local_errno)
{
	int i;

	for (i = 0; i < bsm_errnos_count; i++) {
		if (bsm_errnos[i].be_local_errno == local_errno)
			return (&bsm_errnos[i]);
	}
	return (NULL);
}