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
typedef  int /*<<< orphan*/  attr_val_fifo ;
typedef  int /*<<< orphan*/  attr_val ;

/* Variables and functions */
 int /*<<< orphan*/  UNLINK_FIFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_attr_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
destroy_attr_val_fifo(
	attr_val_fifo *	av_fifo
	)
{
	attr_val *	av;

	if (av_fifo != NULL) {
		for (;;) {
			UNLINK_FIFO(av, *av_fifo, link);
			if (av == NULL)
				break;
			destroy_attr_val(av);
		}
		free(av_fifo);
	}
}