#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {scalar_t__ typecookie; int cmd; int arglen; } ;
struct ng_mesg {TYPE_1__ header; struct ng_checksum_config* data; } ;
struct ng_checksum_stats {int dummy; } ;
struct ng_checksum_config {int csum_flags; int csum_offload; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_5__ {struct ng_checksum_config stats; struct ng_checksum_config* conf; int /*<<< orphan*/  dlt; } ;

/* Variables and functions */
#define  DLT_EN10MB 136 
#define  DLT_RAW 135 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERROUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_CHECKSUM_CLR_STATS 134 
 scalar_t__ NGM_CHECKSUM_COOKIE ; 
#define  NGM_CHECKSUM_GETCLR_STATS 133 
#define  NGM_CHECKSUM_GETCONFIG 132 
#define  NGM_CHECKSUM_GETDLT 131 
#define  NGM_CHECKSUM_GET_STATS 130 
#define  NGM_CHECKSUM_SETCONFIG 129 
#define  NGM_CHECKSUM_SETDLT 128 
 int NG_CHECKSUM_CSUM_IPV4 ; 
 int NG_CHECKSUM_CSUM_IPV6 ; 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  bcopy (struct ng_checksum_config*,struct ng_checksum_config*,int) ; 
 int /*<<< orphan*/  bzero (struct ng_checksum_config*,int) ; 
 int /*<<< orphan*/  free (struct ng_checksum_config*,int /*<<< orphan*/ ) ; 
 struct ng_checksum_config* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ng_checksum_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_checksum_config *conf, *newconf;
	struct ng_mesg *msg;
	struct ng_mesg *resp = NULL;
	int error = 0;

	NGI_GET_MSG(item, msg);

	if  (msg->header.typecookie != NGM_CHECKSUM_COOKIE)
		ERROUT(EINVAL);

	switch (msg->header.cmd)
	{
		case NGM_CHECKSUM_GETDLT:
			NG_MKRESPONSE(resp, msg, sizeof(uint8_t), M_WAITOK);

			if (resp == NULL)
				ERROUT(ENOMEM);

			*((uint8_t *) resp->data) = priv->dlt;

			break;

		case NGM_CHECKSUM_SETDLT:
			if (msg->header.arglen != sizeof(uint8_t))
				ERROUT(EINVAL);

			switch (*(uint8_t *) msg->data)
			{
				case DLT_EN10MB:
				case DLT_RAW:
					priv->dlt = *(uint8_t *) msg->data;
					break;

				default:
					ERROUT(EINVAL);
			}

			break;

		case NGM_CHECKSUM_GETCONFIG:
			if (priv->conf == NULL)
				ERROUT(0);

			NG_MKRESPONSE(resp, msg, sizeof(struct ng_checksum_config), M_WAITOK);

			if (resp == NULL)
				ERROUT(ENOMEM);

			bcopy(priv->conf, resp->data, sizeof(struct ng_checksum_config));

			break;

		case NGM_CHECKSUM_SETCONFIG:
			conf = (struct ng_checksum_config *) msg->data;

			if (msg->header.arglen != sizeof(struct ng_checksum_config))
				ERROUT(EINVAL);

			conf->csum_flags &= NG_CHECKSUM_CSUM_IPV4|NG_CHECKSUM_CSUM_IPV6;
			conf->csum_offload &= NG_CHECKSUM_CSUM_IPV4|NG_CHECKSUM_CSUM_IPV6;

			newconf = malloc(sizeof(struct ng_checksum_config), M_NETGRAPH, M_WAITOK|M_ZERO);

			bcopy(conf, newconf, sizeof(struct ng_checksum_config));

			if (priv->conf)
				free(priv->conf, M_NETGRAPH);

			priv->conf = newconf;

			break;

		case NGM_CHECKSUM_GET_STATS:
		case NGM_CHECKSUM_CLR_STATS:
		case NGM_CHECKSUM_GETCLR_STATS:
			if (msg->header.cmd != NGM_CHECKSUM_CLR_STATS) {
				NG_MKRESPONSE(resp, msg, sizeof(struct ng_checksum_stats), M_WAITOK);

				if (resp == NULL)
					ERROUT(ENOMEM);

				bcopy(&(priv->stats), resp->data, sizeof(struct ng_checksum_stats));
			}

			if (msg->header.cmd != NGM_CHECKSUM_GET_STATS)
				bzero(&(priv->stats), sizeof(struct ng_checksum_stats));

			break;

		default:
			ERROUT(EINVAL);
	}

done:
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);

	return (error);
}