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
struct ead_instance {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  ead_pcap_reopen (int) ; 
 int /*<<< orphan*/  ead_pktloop () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 struct ead_instance* instance ; 
 int /*<<< orphan*/  instance_handle_sigchld ; 
 int /*<<< orphan*/  nonfork ; 
 int /*<<< orphan*/  pcap_close (scalar_t__) ; 
 scalar_t__ pcap_fp ; 
 scalar_t__ pcap_fp_rx ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_server(struct ead_instance *i)
{
	if (!nonfork) {
		i->pid = fork();
		if (i->pid != 0) {
			if (i->pid < 0)
				i->pid = 0;
			return;
		}
	}

	instance = i;
	signal(SIGCHLD, instance_handle_sigchld);
	ead_pcap_reopen(true);
	ead_pktloop();
	pcap_close(pcap_fp);
	if (pcap_fp_rx != pcap_fp)
		pcap_close(pcap_fp_rx);

	exit(0);
}