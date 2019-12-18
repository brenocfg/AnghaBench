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
struct edd_device {int index; int /*<<< orphan*/ * info; int /*<<< orphan*/  mbr_signature; } ;
struct TYPE_2__ {int /*<<< orphan*/ * edd_info; int /*<<< orphan*/ * mbr_signature; } ;

/* Variables and functions */
 TYPE_1__ edd ; 
 scalar_t__ edd_has_edd_info (struct edd_device*) ; 
 scalar_t__ edd_has_mbr_signature (struct edd_device*) ; 

__attribute__((used)) static inline void
edd_dev_set_info(struct edd_device *edev, int i)
{
	edev->index = i;
	if (edd_has_mbr_signature(edev))
		edev->mbr_signature = edd.mbr_signature[i];
	if (edd_has_edd_info(edev))
		edev->info = &edd.edd_info[i];
}