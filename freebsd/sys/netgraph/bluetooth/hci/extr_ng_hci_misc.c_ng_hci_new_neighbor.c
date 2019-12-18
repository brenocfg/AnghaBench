#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ng_hci_unit_p ;
typedef  TYPE_2__* ng_hci_neighbor_p ;
struct TYPE_8__ {int /*<<< orphan*/  updated; } ;
struct TYPE_7__ {int /*<<< orphan*/  neighbors; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_HCI ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  getmicrotime (int /*<<< orphan*/ *) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 

ng_hci_neighbor_p
ng_hci_new_neighbor(ng_hci_unit_p unit)
{
	ng_hci_neighbor_p	n = NULL;

	n = malloc(sizeof(*n), M_NETGRAPH_HCI,
		M_NOWAIT | M_ZERO); 
	if (n != NULL) {
		getmicrotime(&n->updated);
		LIST_INSERT_HEAD(&unit->neighbors, n, next);
	}

	return (n);
}