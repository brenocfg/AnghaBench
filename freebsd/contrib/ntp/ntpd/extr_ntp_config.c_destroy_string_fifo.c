#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* s; } ;
typedef  TYPE_1__ string_node ;
typedef  TYPE_1__ string_fifo ;

/* Variables and functions */
 int /*<<< orphan*/  UNLINK_FIFO (TYPE_1__*,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
destroy_string_fifo(
	string_fifo *	fifo
	)
{
	string_node *	sn;

	if (fifo != NULL) {
		for (;;) {
			UNLINK_FIFO(sn, *fifo, link);
			if (sn == NULL)
				break;
			free(sn->s);
			free(sn);
		}
		free(fifo);
	}
}