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
struct mac_lomac {int ml_flags; } ;

/* Variables and functions */
 int MAC_LOMAC_FLAG_AUX ; 
 int MAC_LOMAC_FLAG_RANGE ; 
 int MAC_LOMAC_FLAG_SINGLE ; 
 int /*<<< orphan*/  lomac_copy_auxsingle (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_copy_range (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_copy_single (struct mac_lomac*,struct mac_lomac*) ; 

__attribute__((used)) static void
lomac_copy(struct mac_lomac *source, struct mac_lomac *dest)
{

	if (source->ml_flags & MAC_LOMAC_FLAG_SINGLE)
		lomac_copy_single(source, dest);
	if (source->ml_flags & MAC_LOMAC_FLAG_AUX)
		lomac_copy_auxsingle(source, dest);
	if (source->ml_flags & MAC_LOMAC_FLAG_RANGE)
		lomac_copy_range(source, dest);
}