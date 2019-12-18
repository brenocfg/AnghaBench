#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int typecookie; int const cmd; int arglen; } ;
struct ng_mesg {TYPE_3__ header; scalar_t__ data; } ;
struct TYPE_13__ {int opt; int cir; int pir; int cbs; int ebs; int /*<<< orphan*/  mode; } ;
struct ng_car_bulkstats {TYPE_5__ upstream; TYPE_5__ downstream; } ;
struct ng_car_bulkconf {TYPE_5__ upstream; TYPE_5__ downstream; } ;
typedef  TYPE_4__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_10__ {int tc; int te; TYPE_5__ conf; TYPE_5__ stats; } ;
struct TYPE_9__ {int tc; int te; TYPE_5__ conf; TYPE_5__ stats; } ;
struct TYPE_12__ {TYPE_2__ lower; TYPE_1__ upper; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_CAR_CLR_STATS 133 
#define  NGM_CAR_COOKIE 132 
#define  NGM_CAR_GETCLR_STATS 131 
#define  NGM_CAR_GET_CONF 130 
#define  NGM_CAR_GET_STATS 129 
#define  NGM_CAR_SET_CONF 128 
 int NG_CAR_COUNT_PACKETS ; 
 int /*<<< orphan*/  NG_CAR_RED ; 
 int /*<<< orphan*/  NG_CAR_SHAPE ; 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  bcopy (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 

__attribute__((used)) static int
ng_car_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_mesg *resp = NULL;
	int error = 0;
	struct ng_mesg *msg;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_CAR_COOKIE:
		switch (msg->header.cmd) {
		case NGM_CAR_GET_STATS:
		case NGM_CAR_GETCLR_STATS:
			{
				struct ng_car_bulkstats *bstats;

				NG_MKRESPONSE(resp, msg,
					sizeof(*bstats), M_NOWAIT);
				if (resp == NULL) {
					error = ENOMEM;
					break;
				}
				bstats = (struct ng_car_bulkstats *)resp->data;

				bcopy(&priv->upper.stats, &bstats->downstream,
				    sizeof(bstats->downstream));
				bcopy(&priv->lower.stats, &bstats->upstream,
				    sizeof(bstats->upstream));
			}
			if (msg->header.cmd == NGM_CAR_GET_STATS)
				break;
		case NGM_CAR_CLR_STATS:
			bzero(&priv->upper.stats,
				sizeof(priv->upper.stats));
			bzero(&priv->lower.stats,
				sizeof(priv->lower.stats));
			break;
		case NGM_CAR_GET_CONF:
			{
				struct ng_car_bulkconf *bconf;

				NG_MKRESPONSE(resp, msg,
					sizeof(*bconf), M_NOWAIT);
				if (resp == NULL) {
					error = ENOMEM;
					break;
				}
				bconf = (struct ng_car_bulkconf *)resp->data;

				bcopy(&priv->upper.conf, &bconf->downstream,
				    sizeof(bconf->downstream));
				bcopy(&priv->lower.conf, &bconf->upstream,
				    sizeof(bconf->upstream));
				/* Convert internal 1/(8*128) of pps into pps */
				if (bconf->downstream.opt & NG_CAR_COUNT_PACKETS) {
				    bconf->downstream.cir /= 1024;
				    bconf->downstream.pir /= 1024;
				    bconf->downstream.cbs /= 128;
				    bconf->downstream.ebs /= 128;
				}
				if (bconf->upstream.opt & NG_CAR_COUNT_PACKETS) {
				    bconf->upstream.cir /= 1024;
				    bconf->upstream.pir /= 1024;
				    bconf->upstream.cbs /= 128;
				    bconf->upstream.ebs /= 128;
				}
			}
			break;
		case NGM_CAR_SET_CONF:
			{
				struct ng_car_bulkconf *const bconf =
				(struct ng_car_bulkconf *)msg->data;

				/* Check for invalid or illegal config. */
				if (msg->header.arglen != sizeof(*bconf)) {
					error = EINVAL;
					break;
				}
				/* Convert pps into internal 1/(8*128) of pps */
				if (bconf->downstream.opt & NG_CAR_COUNT_PACKETS) {
				    bconf->downstream.cir *= 1024;
				    bconf->downstream.pir *= 1024;
				    bconf->downstream.cbs *= 125;
				    bconf->downstream.ebs *= 125;
				}
				if (bconf->upstream.opt & NG_CAR_COUNT_PACKETS) {
				    bconf->upstream.cir *= 1024;
				    bconf->upstream.pir *= 1024;
				    bconf->upstream.cbs *= 125;
				    bconf->upstream.ebs *= 125;
				}
				if ((bconf->downstream.cir > 1000000000) ||
				    (bconf->downstream.pir > 1000000000) ||
				    (bconf->upstream.cir > 1000000000) ||
				    (bconf->upstream.pir > 1000000000) ||
				    (bconf->downstream.cbs == 0 &&
					bconf->downstream.ebs == 0) ||
				    (bconf->upstream.cbs == 0 &&
					bconf->upstream.ebs == 0))
				{
					error = EINVAL;
					break;
				}
				if ((bconf->upstream.mode == NG_CAR_SHAPE) &&
				    (bconf->upstream.cir == 0)) {
					error = EINVAL;
					break;
				}
				if ((bconf->downstream.mode == NG_CAR_SHAPE) &&
				    (bconf->downstream.cir == 0)) {
					error = EINVAL;
					break;
				}

				/* Copy downstream config. */
				bcopy(&bconf->downstream, &priv->upper.conf,
				    sizeof(priv->upper.conf));
    				priv->upper.tc = priv->upper.conf.cbs;
				if (priv->upper.conf.mode == NG_CAR_RED ||
				    priv->upper.conf.mode == NG_CAR_SHAPE) {
					priv->upper.te = 0;
				} else {
					priv->upper.te = priv->upper.conf.ebs;
				}

				/* Copy upstream config. */
				bcopy(&bconf->upstream, &priv->lower.conf,
				    sizeof(priv->lower.conf));
    				priv->lower.tc = priv->lower.conf.cbs;
				if (priv->lower.conf.mode == NG_CAR_RED ||
				    priv->lower.conf.mode == NG_CAR_SHAPE) {
					priv->lower.te = 0;
				} else {
					priv->lower.te = priv->lower.conf.ebs;
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