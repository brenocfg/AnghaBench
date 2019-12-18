#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pid; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/  dag_platform_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_pcap_dag (int /*<<< orphan*/ *) ; 
 scalar_t__ getpid () ; 
 TYPE_1__* pcap_dags ; 

__attribute__((used)) static void
atexit_handler(void)
{
	while (pcap_dags != NULL) {
		if (pcap_dags->pid == getpid()) {
			if (pcap_dags->p != NULL)
				dag_platform_cleanup(pcap_dags->p);
		} else {
			delete_pcap_dag(pcap_dags->p);
		}
	}
}