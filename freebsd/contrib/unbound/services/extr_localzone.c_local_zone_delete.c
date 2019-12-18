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
struct local_zone {struct local_zone* taglist; struct local_zone* name; int /*<<< orphan*/  region; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct local_zone*) ; 
 int /*<<< orphan*/  lock_rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regional_destroy (int /*<<< orphan*/ ) ; 

void 
local_zone_delete(struct local_zone* z)
{
	if(!z)
		return;
	lock_rw_destroy(&z->lock);
	regional_destroy(z->region);
	free(z->name);
	free(z->taglist);
	free(z);
}