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
typedef  int /*<<< orphan*/  int_node ;
typedef  int /*<<< orphan*/  int_fifo ;

/* Variables and functions */
 int /*<<< orphan*/  UNLINK_FIFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
destroy_int_fifo(
	int_fifo *	fifo
	)
{
	int_node *	i_n;

	if (fifo != NULL) {
		for (;;) {
			UNLINK_FIFO(i_n, *fifo, link);
			if (i_n == NULL)
				break;
			free(i_n);
		}
		free(fifo);
	}
}