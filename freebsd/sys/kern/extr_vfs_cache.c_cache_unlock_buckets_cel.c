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
struct celockstate {int /*<<< orphan*/ ** blp; } ;

/* Variables and functions */
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cache_unlock_buckets_cel(struct celockstate *cel)
{

	if (cel->blp[0] != NULL)
		rw_wunlock(cel->blp[0]);
	rw_wunlock(cel->blp[1]);
}