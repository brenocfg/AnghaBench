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
typedef  enum kvm_page_track_mode { ____Placeholder_kvm_page_track_mode } kvm_page_track_mode ;

/* Variables and functions */
 int KVM_PAGE_TRACK_MAX ; 

__attribute__((used)) static inline bool page_track_mode_is_valid(enum kvm_page_track_mode mode)
{
	if (mode < 0 || mode >= KVM_PAGE_TRACK_MAX)
		return false;

	return true;
}