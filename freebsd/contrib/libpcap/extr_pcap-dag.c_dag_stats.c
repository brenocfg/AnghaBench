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
typedef  int /*<<< orphan*/  uint32_t ;
struct pcap_stat {int /*<<< orphan*/  ps_drop; } ;
struct pcap_dag {scalar_t__ drop_attr; struct pcap_stat stat; int /*<<< orphan*/  dag_ref; } ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; struct pcap_dag* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int dag_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 scalar_t__ dag_config_get_uint32_attribute_ex (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dag_config_strerror (int) ; 
 scalar_t__ kDagErrNone ; 
 scalar_t__ kNullAttributeUuid ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dag_stats(pcap_t *p, struct pcap_stat *ps) {
	struct pcap_dag *pd = p->priv;
	uint32_t stream_drop;
	dag_err_t dag_error;

	/*
	 * Packet records received (ps_recv) are counted in dag_read().
	 * Packet records dropped (ps_drop) are read from Stream Drop attribute if present,
	 * otherwise integrate the ERF Header lctr counts (if available) in dag_read().
	 * We are reporting that no records are dropped by the card/driver (ps_ifdrop).
	 */

	if(pd->drop_attr != kNullAttributeUuid) {
		/* Note this counter is cleared at start of capture and will wrap at UINT_MAX.
		 * The application is responsible for polling ps_drop frequently enough
		 * to detect each wrap and integrate total drop with a wider counter */
		if ((dag_error = dag_config_get_uint32_attribute_ex(pd->dag_ref, pd->drop_attr, &stream_drop) == kDagErrNone)) {
			pd->stat.ps_drop = stream_drop;
		} else {
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "reading stream drop attribute: %s",
				 dag_config_strerror(dag_error));
			return -1;
		}
	}

	*ps = pd->stat;

	return 0;
}