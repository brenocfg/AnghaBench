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

/* Variables and functions */
 int /*<<< orphan*/  capsule_pending ; 
 int efi_reset_type ; 

bool efi_capsule_pending(int *reset_type)
{
	if (!capsule_pending)
		return false;

	if (reset_type)
		*reset_type = efi_reset_type;

	return true;
}