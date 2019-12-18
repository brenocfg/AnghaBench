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
struct rpcap_header {int /*<<< orphan*/  plen; } ;
struct pcap_rpcap {scalar_t__ rmt_sockctrl; scalar_t__ rmt_sockdata; int /*<<< orphan*/ * currentfilter; int /*<<< orphan*/  protocol_version; } ;
struct activehosts {scalar_t__ sockctrl; struct activehosts* next; } ;
struct TYPE_3__ {struct pcap_rpcap* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  RPCAP_MSG_CLOSE ; 
 int /*<<< orphan*/  RPCAP_MSG_ENDCAP_REQ ; 
 struct activehosts* activeHosts ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcap_createhdr (struct rpcap_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcap_discard (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rpcap_process_msg_header (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpcap_header*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_cleanup () ; 
 int /*<<< orphan*/  sock_close (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_send (scalar_t__,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcap_cleanup_rpcap(pcap_t *fp)
{
	struct pcap_rpcap *pr = fp->priv;	/* structure used when doing a remote live capture */
	struct rpcap_header header;		/* header of the RPCAP packet */
	struct activehosts *temp;		/* temp var needed to scan the host list chain, to detect if we're in active mode */
	int active = 0;				/* active mode or not? */

	/* detect if we're in active mode */
	temp = activeHosts;
	while (temp)
	{
		if (temp->sockctrl == pr->rmt_sockctrl)
		{
			active = 1;
			break;
		}
		temp = temp->next;
	}

	if (!active)
	{
		rpcap_createhdr(&header, pr->protocol_version,
		    RPCAP_MSG_CLOSE, 0, 0);

		/*
		 * Send the close request; don't report any errors, as
		 * we're closing this pcap_t, and have no place to report
		 * the error.  No reply is sent to this message.
		 */
		(void)sock_send(pr->rmt_sockctrl, (char *)&header,
		    sizeof(struct rpcap_header), NULL, 0);
	}
	else
	{
		rpcap_createhdr(&header, pr->protocol_version,
		    RPCAP_MSG_ENDCAP_REQ, 0, 0);

		/*
		 * Send the end capture request; don't report any errors,
		 * as we're closing this pcap_t, and have no place to
		 * report the error.
		 */
		if (sock_send(pr->rmt_sockctrl, (char *)&header,
		    sizeof(struct rpcap_header), NULL, 0) == 0)
		{
			/*
			 * Wait for the answer; don't report any errors,
			 * as we're closing this pcap_t, and have no
			 * place to report the error.
			 */
			if (rpcap_process_msg_header(pr->rmt_sockctrl,
			    pr->protocol_version, RPCAP_MSG_ENDCAP_REQ,
			    &header, NULL) == 0)
			{
				(void)rpcap_discard(pr->rmt_sockctrl,
				    header.plen, NULL);
			}
		}
	}

	if (pr->rmt_sockdata)
	{
		sock_close(pr->rmt_sockdata, NULL, 0);
		pr->rmt_sockdata = 0;
	}

	if ((!active) && (pr->rmt_sockctrl))
		sock_close(pr->rmt_sockctrl, NULL, 0);

	pr->rmt_sockctrl = 0;

	if (pr->currentfilter)
	{
		free(pr->currentfilter);
		pr->currentfilter = NULL;
	}

	/* To avoid inconsistencies in the number of sock_init() */
	sock_cleanup();
}