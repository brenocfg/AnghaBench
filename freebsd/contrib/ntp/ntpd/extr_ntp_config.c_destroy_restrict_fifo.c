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
typedef  int /*<<< orphan*/  restrict_node ;
typedef  int /*<<< orphan*/  restrict_fifo ;

/* Variables and functions */
 int /*<<< orphan*/  UNLINK_FIFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_restrict_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
destroy_restrict_fifo(
	restrict_fifo *	fifo
	)
{
	restrict_node *	rn;

	if (fifo != NULL) {
		for (;;) {
			UNLINK_FIFO(rn, *fifo, link);
			if (rn == NULL)
				break;
			destroy_restrict_node(rn);
		}
		free(fifo);
	}
}