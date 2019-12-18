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
struct diff_filespec {int /*<<< orphan*/ * data; scalar_t__ should_munmap; scalar_t__ should_free; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void diff_free_filespec_blob(struct diff_filespec *s)
{
	if (s->should_free)
		free(s->data);
	else if (s->should_munmap)
		munmap(s->data, s->size);

	if (s->should_free || s->should_munmap) {
		s->should_free = s->should_munmap = 0;
		s->data = NULL;
	}
}