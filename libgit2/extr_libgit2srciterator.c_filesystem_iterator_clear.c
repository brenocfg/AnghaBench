#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {int /*<<< orphan*/  base; int /*<<< orphan*/  tmp_buf; int /*<<< orphan*/  ignores; TYPE_2__ frames; } ;
typedef  TYPE_1__ filesystem_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  filesystem_iterator_frame_pop (TYPE_1__*) ; 
 int /*<<< orphan*/  git_array_clear (TYPE_2__) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_ignore__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterator_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void filesystem_iterator_clear(filesystem_iterator *iter)
{
	while (iter->frames.size)
		filesystem_iterator_frame_pop(iter);

	git_array_clear(iter->frames);
	git_ignore__free(&iter->ignores);

	git_buf_dispose(&iter->tmp_buf);

	iterator_clear(&iter->base);
}