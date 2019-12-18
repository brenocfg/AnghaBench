#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  portid_display ;
struct TYPE_7__ {int /*<<< orphan*/  display_name; } ;
typedef  TYPE_2__ ocs_sport_t ;
struct TYPE_6__ {int /*<<< orphan*/  fc_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  display_name; TYPE_2__* sport; TYPE_1__ rnode; } ;
typedef  TYPE_3__ ocs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_assert (TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_node_fcid_display (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ocs_snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,char*) ; 

void
ocs_node_update_display_name(ocs_node_t *node)
{
	uint32_t port_id = node->rnode.fc_id;
	ocs_sport_t *sport = node->sport;
	char portid_display[16];

	ocs_assert(sport);

	ocs_node_fcid_display(port_id, portid_display, sizeof(portid_display));

	ocs_snprintf(node->display_name, sizeof(node->display_name), "%s.%s", sport->display_name, portid_display);
}