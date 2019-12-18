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
struct TYPE_7__ {int /*<<< orphan*/  options; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ addr_opts_node ;
typedef  TYPE_1__ addr_opts_fifo ;

/* Variables and functions */
 int /*<<< orphan*/  UNLINK_FIFO (TYPE_1__*,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_address_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_attr_val_fifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
destroy_addr_opts_fifo(
	addr_opts_fifo *	fifo
	)
{
	addr_opts_node *	aon;

	if (fifo != NULL) {
		for (;;) {
			UNLINK_FIFO(aon, *fifo, link);
			if (aon == NULL)
				break;
			destroy_address_node(aon->addr);
			destroy_attr_val_fifo(aon->options);
			free(aon);
		}
		free(fifo);
	}
}