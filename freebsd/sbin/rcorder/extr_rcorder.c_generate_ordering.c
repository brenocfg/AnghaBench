#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;
struct TYPE_3__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_file (TYPE_2__*) ; 
 TYPE_1__* fn_head ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
generate_ordering(void)
{

	/*
	 * while there remain undone files{f},
	 *	pick an arbitrary f, and do_file(f)
	 * Note that the first file in the file list is perfectly
	 * arbitrary, and easy to find, so we use that.
	 */

	/*
	 * N.B.: the file nodes "self delete" after they execute, so
	 * after each iteration of the loop, the head will be pointing
	 * to something totally different. The loop ends up being
	 * executed only once for every strongly connected set of
	 * nodes.
	 */
	while (fn_head->next != NULL) {
		DPRINTF((stderr, "generate on %s\n", fn_head->next->filename));
		do_file(fn_head->next);
	}
}