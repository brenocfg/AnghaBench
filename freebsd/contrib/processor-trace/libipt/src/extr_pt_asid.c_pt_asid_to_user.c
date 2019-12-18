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
struct pt_asid {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct pt_asid*,struct pt_asid const*,size_t) ; 
 int pte_internal ; 
 int pte_invalid ; 

int pt_asid_to_user(struct pt_asid *user, const struct pt_asid *asid,
		    size_t size)
{
	if (!user || !asid)
		return -pte_internal;

	/* We need at least space for the size field. */
	if (size < sizeof(asid->size))
		return -pte_invalid;

	/* Only provide the fields we actually have. */
	if (sizeof(*asid) < size)
		size = sizeof(*asid);

	/* Copy (portions of) our asid to the user's. */
	memcpy(user, asid, size);

	/* We copied our size - fix it. */
	user->size = size;

	return 0;
}