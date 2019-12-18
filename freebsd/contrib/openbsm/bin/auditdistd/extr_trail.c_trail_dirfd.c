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
struct trail {scalar_t__ tr_magic; int /*<<< orphan*/  tr_dirfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ TRAIL_MAGIC ; 
 int dirfd (int /*<<< orphan*/ ) ; 

int
trail_dirfd(const struct trail *trail)
{

	PJDLOG_ASSERT(trail->tr_magic == TRAIL_MAGIC);

	return (dirfd(trail->tr_dirfp));
}