#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  print_desc; int /*<<< orphan*/  port_num; int /*<<< orphan*/  node_guid; } ;
typedef  TYPE_1__ port_report_t ;

/* Variables and functions */
 scalar_t__ IB_NODE_DESCRIPTION_SIZE ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
__tag_port_report(port_report_t ** head, uint64_t node_guid,
		  uint8_t port_num, char *print_desc)
{
	port_report_t *rep = malloc(sizeof(*rep));
	if (!rep)
		return;

	rep->node_guid = node_guid;
	rep->port_num = port_num;
	memcpy(rep->print_desc, print_desc, IB_NODE_DESCRIPTION_SIZE + 1);
	rep->next = NULL;
	if (*head) {
		rep->next = *head;
		*head = rep;
	} else
		*head = rep;
}