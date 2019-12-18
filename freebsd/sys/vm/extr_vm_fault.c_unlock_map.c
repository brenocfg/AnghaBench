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
struct faultstate {int lookup_still_valid; int /*<<< orphan*/  entry; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_map_lookup_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
unlock_map(struct faultstate *fs)
{

	if (fs->lookup_still_valid) {
		vm_map_lookup_done(fs->map, fs->entry);
		fs->lookup_still_valid = false;
	}
}