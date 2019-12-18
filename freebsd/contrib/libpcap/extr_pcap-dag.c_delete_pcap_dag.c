#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pcap_t ;
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ pcap_dag_node_t ;

/* Variables and functions */
 TYPE_1__* pcap_dags ; 

__attribute__((used)) static void
delete_pcap_dag(pcap_t *p)
{
	pcap_dag_node_t *curr = NULL, *prev = NULL;

	for (prev = NULL, curr = pcap_dags; curr != NULL && curr->p != p; prev = curr, curr = curr->next) {
		/* empty */
	}

	if (curr != NULL && curr->p == p) {
		if (prev != NULL) {
			prev->next = curr->next;
		} else {
			pcap_dags = curr->next;
		}
	}
}