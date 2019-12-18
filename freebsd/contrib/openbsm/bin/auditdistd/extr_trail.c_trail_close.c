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
struct trail {scalar_t__ tr_magic; int tr_filefd; char* tr_filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
 scalar_t__ TRAIL_MAGIC ; 
 scalar_t__ close (int) ; 

void
trail_close(struct trail *trail)
{

	PJDLOG_ASSERT(trail->tr_magic == TRAIL_MAGIC);
	PJDLOG_ASSERT(trail->tr_filefd >= 0);
	PJDLOG_ASSERT(trail->tr_filename[0] != '\0');

	PJDLOG_VERIFY(close(trail->tr_filefd) == 0);
	trail->tr_filefd = -1;
}