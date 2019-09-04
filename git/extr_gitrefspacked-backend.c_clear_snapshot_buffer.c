#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snapshot {int /*<<< orphan*/ * eof; int /*<<< orphan*/ * start; int /*<<< orphan*/ * buf; scalar_t__ mmapped; TYPE_1__* refs; } ;
struct TYPE_2__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  die_errno (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ munmap (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void clear_snapshot_buffer(struct snapshot *snapshot)
{
	if (snapshot->mmapped) {
		if (munmap(snapshot->buf, snapshot->eof - snapshot->buf))
			die_errno("error ummapping packed-refs file %s",
				  snapshot->refs->path);
		snapshot->mmapped = 0;
	} else {
		free(snapshot->buf);
	}
	snapshot->buf = snapshot->start = snapshot->eof = NULL;
}