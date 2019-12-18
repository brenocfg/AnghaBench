#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int bandwidth; } ;
struct ng_pipe_stats {TYPE_4__ upstream; TYPE_4__ downstream; } ;
struct ng_pipe_run {TYPE_4__ upstream; TYPE_4__ downstream; } ;
struct ng_pipe_cfg {int delay; int overhead; int header_offset; int bandwidth; TYPE_4__ upstream; TYPE_4__ downstream; } ;
struct TYPE_11__ {int typecookie; int const cmd; int arglen; } ;
struct ng_mesg {TYPE_1__ header; scalar_t__ data; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_13__ {int bandwidth; int ber; } ;
struct TYPE_15__ {int /*<<< orphan*/ * hook; TYPE_3__ cfg; TYPE_3__ run; TYPE_3__ stats; } ;
struct TYPE_12__ {int delay; int overhead; int header_offset; TYPE_5__ upper; TYPE_5__ lower; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MAX_OHSIZE ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  NGM_FLOW_COOKIE ; 
 int NGM_LINK_IS_DOWN ; 
 int NGM_LINK_IS_UP ; 
#define  NGM_PIPE_CLR_STATS 134 
#define  NGM_PIPE_COOKIE 133 
#define  NGM_PIPE_GETCLR_STATS 132 
#define  NGM_PIPE_GET_CFG 131 
#define  NGM_PIPE_GET_RUN 130 
#define  NGM_PIPE_GET_STATS 129 
#define  NGM_PIPE_SET_CFG 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKMESSAGE (struct ng_mesg*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_SEND_MSG_HOOK (int,int /*<<< orphan*/ ,struct ng_mesg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  parse_cfg (TYPE_3__*,TYPE_4__*,TYPE_5__*,TYPE_2__* const) ; 

__attribute__((used)) static int
ngp_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_mesg *resp = NULL;
	struct ng_mesg *msg, *flow_msg;
	struct ng_pipe_stats *stats;
	struct ng_pipe_run *run;
	struct ng_pipe_cfg *cfg;
	int error = 0;
	int prev_down, now_down, cmd;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_PIPE_COOKIE:
		switch (msg->header.cmd) {
		case NGM_PIPE_GET_STATS:
		case NGM_PIPE_CLR_STATS:
		case NGM_PIPE_GETCLR_STATS:
			if (msg->header.cmd != NGM_PIPE_CLR_STATS) {
				NG_MKRESPONSE(resp, msg,
				    sizeof(*stats), M_NOWAIT);
				if (resp == NULL) {
					error = ENOMEM;
					break;
				}
				stats = (struct ng_pipe_stats *) resp->data;
				bcopy(&priv->upper.stats, &stats->downstream,
				    sizeof(stats->downstream));
				bcopy(&priv->lower.stats, &stats->upstream,
				    sizeof(stats->upstream));
			}
			if (msg->header.cmd != NGM_PIPE_GET_STATS) {
				bzero(&priv->upper.stats,
				    sizeof(priv->upper.stats));
				bzero(&priv->lower.stats,
				    sizeof(priv->lower.stats));
			}
			break;
		case NGM_PIPE_GET_RUN:
			NG_MKRESPONSE(resp, msg, sizeof(*run), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			run = (struct ng_pipe_run *) resp->data;
			bcopy(&priv->upper.run, &run->downstream,
				sizeof(run->downstream));
			bcopy(&priv->lower.run, &run->upstream,
				sizeof(run->upstream));
			break;
		case NGM_PIPE_GET_CFG:
			NG_MKRESPONSE(resp, msg, sizeof(*cfg), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				break;
			}
			cfg = (struct ng_pipe_cfg *) resp->data;
			bcopy(&priv->upper.cfg, &cfg->downstream,
				sizeof(cfg->downstream));
			bcopy(&priv->lower.cfg, &cfg->upstream,
				sizeof(cfg->upstream));
			cfg->delay = priv->delay;
			cfg->overhead = priv->overhead;
			cfg->header_offset = priv->header_offset;
			if (cfg->upstream.bandwidth ==
			    cfg->downstream.bandwidth) {
				cfg->bandwidth = cfg->upstream.bandwidth;
				cfg->upstream.bandwidth = 0;
				cfg->downstream.bandwidth = 0;
			} else
				cfg->bandwidth = 0;
			break;
		case NGM_PIPE_SET_CFG:
			cfg = (struct ng_pipe_cfg *) msg->data;
			if (msg->header.arglen != sizeof(*cfg)) {
				error = EINVAL;
				break;
			}

			if (cfg->delay == -1)
				priv->delay = 0;
			else if (cfg->delay > 0 && cfg->delay < 10000000)
				priv->delay = cfg->delay;

			if (cfg->bandwidth == -1) {
				priv->upper.cfg.bandwidth = 0;
				priv->lower.cfg.bandwidth = 0;
				priv->overhead = 0;
			} else if (cfg->bandwidth >= 100 &&
			    cfg->bandwidth <= 1000000000) {
				priv->upper.cfg.bandwidth = cfg->bandwidth;
				priv->lower.cfg.bandwidth = cfg->bandwidth;
				if (cfg->bandwidth >= 10000000)
					priv->overhead = 8+4+12; /* Ethernet */
				else
					priv->overhead = 10; /* HDLC */
			}

			if (cfg->overhead == -1)
				priv->overhead = 0;
			else if (cfg->overhead > 0 &&
			    cfg->overhead < MAX_OHSIZE)
				priv->overhead = cfg->overhead;

			if (cfg->header_offset == -1)
				priv->header_offset = 0;
			else if (cfg->header_offset > 0 &&
			    cfg->header_offset < 64)
				priv->header_offset = cfg->header_offset;

			prev_down = priv->upper.cfg.ber == 1 ||
			    priv->lower.cfg.ber == 1;
			parse_cfg(&priv->upper.cfg, &cfg->downstream,
			    &priv->upper, priv);
			parse_cfg(&priv->lower.cfg, &cfg->upstream,
			    &priv->lower, priv);
			now_down = priv->upper.cfg.ber == 1 ||
			    priv->lower.cfg.ber == 1;

			if (prev_down != now_down) {
				if (now_down)
					cmd = NGM_LINK_IS_DOWN;
				else
					cmd = NGM_LINK_IS_UP;

				if (priv->lower.hook != NULL) {
					NG_MKMESSAGE(flow_msg, NGM_FLOW_COOKIE,
					    cmd, 0, M_NOWAIT);
					if (flow_msg != NULL)
						NG_SEND_MSG_HOOK(error, node,
						    flow_msg, priv->lower.hook,
						    0);
				}
				if (priv->upper.hook != NULL) {
					NG_MKMESSAGE(flow_msg, NGM_FLOW_COOKIE,
					    cmd, 0, M_NOWAIT);
					if (flow_msg != NULL)
						NG_SEND_MSG_HOOK(error, node,
						    flow_msg, priv->upper.hook,
						    0);
				}
			}
			break;
		default:
			error = EINVAL;
			break;
		}
		break;
	default:
		error = EINVAL;
		break;
	}
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);

	return (error);
}