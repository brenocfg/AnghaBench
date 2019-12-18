#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pcap_dag {int /*<<< orphan*/ * dag_ref; int /*<<< orphan*/  dag_stream; } ;
struct TYPE_5__ {int fd; struct pcap_dag* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  dag_config_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ dag_detach_stream (int,int /*<<< orphan*/ ) ; 
 scalar_t__ dag_stop_stream (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_pcap_dag (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dag_platform_cleanup(pcap_t *p)
{
	struct pcap_dag *pd = p->priv;

	if(dag_stop_stream(p->fd, pd->dag_stream) < 0)
		fprintf(stderr,"dag_stop_stream: %s\n", strerror(errno));

	if(dag_detach_stream(p->fd, pd->dag_stream) < 0)
		fprintf(stderr,"dag_detach_stream: %s\n", strerror(errno));

	if(pd->dag_ref != NULL) {
		dag_config_dispose(pd->dag_ref);
		p->fd = -1;
		pd->dag_ref = NULL;
	}
	delete_pcap_dag(p);
	pcap_cleanup_live_common(p);
	/* Note: don't need to call close(p->fd) or dag_close(p->fd) as dag_config_dispose(pd->dag_ref) does this. */
}