#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* iffam_p ;
struct TYPE_4__ {int /*<<< orphan*/  hookname; } ;

/* Variables and functions */
 int NUM_FAMILIES ; 
 TYPE_1__* gFamilies ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static __inline iffam_p
get_iffam_from_name(const char *name)
{
	iffam_p iffam;
	int k;

	for (k = 0; k < NUM_FAMILIES; k++) {
		iffam = &gFamilies[k];
		if (!strcmp(iffam->hookname, name))
			return (iffam);
	}
	return (NULL);
}