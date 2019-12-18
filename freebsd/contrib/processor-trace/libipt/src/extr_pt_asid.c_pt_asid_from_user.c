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
 int /*<<< orphan*/  pt_asid_init (struct pt_asid*) ; 
 int pte_internal ; 

int pt_asid_from_user(struct pt_asid *asid, const struct pt_asid *user)
{
	if (!asid)
		return -pte_internal;

	pt_asid_init(asid);

	if (user) {
		size_t size;

		size = user->size;

		/* Ignore fields in the user's asid we don't know. */
		if (sizeof(*asid) < size)
			size = sizeof(*asid);

		/* Copy (portions of) the user's asid. */
		memcpy(asid, user, size);

		/* We copied user's size - fix it. */
		asid->size = sizeof(*asid);
	}

	return 0;
}