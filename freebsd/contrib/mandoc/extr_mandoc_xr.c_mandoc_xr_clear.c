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
struct mandoc_xr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mandoc_xr*) ; 
 int /*<<< orphan*/  ohash_delete (int /*<<< orphan*/ *) ; 
 struct mandoc_xr* ohash_first (int /*<<< orphan*/ *,unsigned int*) ; 
 struct mandoc_xr* ohash_next (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/ * xr_hash ; 

__attribute__((used)) static void
mandoc_xr_clear(void)
{
	struct mandoc_xr	*xr;
	unsigned int		 slot;

	if (xr_hash == NULL)
		return;
	for (xr = ohash_first(xr_hash, &slot); xr != NULL;
	     xr = ohash_next(xr_hash, &slot))
		free(xr);
	ohash_delete(xr_hash);
}