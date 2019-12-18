#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ng_source_stats {size_t index; int width; int /*<<< orphan*/  maxPps; int /*<<< orphan*/  startTime; int /*<<< orphan*/  elapsedTime; int /*<<< orphan*/  endTime; int /*<<< orphan*/  queueFrames; int /*<<< orphan*/  queueOctets; } ;
struct ng_source_embed_info {size_t index; int width; int /*<<< orphan*/  maxPps; int /*<<< orphan*/  startTime; int /*<<< orphan*/  elapsedTime; int /*<<< orphan*/  endTime; int /*<<< orphan*/  queueFrames; int /*<<< orphan*/  queueOctets; } ;
struct ng_source_embed_cnt_info {size_t index; int width; int /*<<< orphan*/  maxPps; int /*<<< orphan*/  startTime; int /*<<< orphan*/  elapsedTime; int /*<<< orphan*/  endTime; int /*<<< orphan*/  queueFrames; int /*<<< orphan*/  queueOctets; } ;
struct TYPE_13__ {int typecookie; int flags; int const cmd; int arglen; } ;
struct ng_mesg {TYPE_3__ header; scalar_t__ data; } ;
typedef  TYPE_4__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_11__ {int /*<<< orphan*/  ifq_len; } ;
struct TYPE_14__ {struct ng_source_stats* embed_counter; struct ng_source_stats embed_timestamp; struct ng_source_stats stats; TYPE_2__* node; TYPE_1__ snd_queue; int /*<<< orphan*/  queueOctets; } ;
struct TYPE_12__ {int nd_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int NGF_RESP ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_ETHER_COOKIE 142 
#define  NGM_ETHER_GET_IFNAME 141 
#define  NGM_SOURCE_CLR_DATA 140 
#define  NGM_SOURCE_CLR_STATS 139 
#define  NGM_SOURCE_COOKIE 138 
#define  NGM_SOURCE_GETCLR_STATS 137 
#define  NGM_SOURCE_GET_COUNTER 136 
#define  NGM_SOURCE_GET_STATS 135 
#define  NGM_SOURCE_GET_TIMESTAMP 134 
#define  NGM_SOURCE_SETIFACE 133 
#define  NGM_SOURCE_SETPPS 132 
#define  NGM_SOURCE_SET_COUNTER 131 
#define  NGM_SOURCE_SET_TIMESTAMP 130 
#define  NGM_SOURCE_START 129 
#define  NGM_SOURCE_STOP 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int NG_SOURCE_ACTIVE ; 
 size_t NG_SOURCE_COUNTERS ; 
 int /*<<< orphan*/  bcopy (struct ng_source_stats*,struct ng_source_stats*,int) ; 
 int /*<<< orphan*/  bzero (struct ng_source_stats*,int) ; 
 int /*<<< orphan*/  getmicrotime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_source_clr_data (TYPE_4__*) ; 
 int /*<<< orphan*/  ng_source_set_autosrc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ng_source_start (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_source_stop (TYPE_4__*) ; 
 int /*<<< orphan*/  ng_source_store_output_ifp (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  timevalisset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timevalsub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_source_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	sc_p sc = NG_NODE_PRIVATE(node);
	struct ng_mesg *msg, *resp = NULL;
	int error = 0;

	NGI_GET_MSG(item, msg);

	switch (msg->header.typecookie) {
	case NGM_SOURCE_COOKIE:
		if (msg->header.flags & NGF_RESP) {
			error = EINVAL;
			break;
		}
		switch (msg->header.cmd) {
		case NGM_SOURCE_GET_STATS:
		case NGM_SOURCE_CLR_STATS:
		case NGM_SOURCE_GETCLR_STATS:
                    {
			struct ng_source_stats *stats;

                        if (msg->header.cmd != NGM_SOURCE_CLR_STATS) {
                                NG_MKRESPONSE(resp, msg,
                                    sizeof(*stats), M_NOWAIT);
				if (resp == NULL) {
					error = ENOMEM;
					goto done;
				}
				sc->stats.queueOctets = sc->queueOctets;
				sc->stats.queueFrames = sc->snd_queue.ifq_len;
				if ((sc->node->nd_flags & NG_SOURCE_ACTIVE)
				    && !timevalisset(&sc->stats.endTime)) {
					getmicrotime(&sc->stats.elapsedTime);
					timevalsub(&sc->stats.elapsedTime,
					    &sc->stats.startTime);
				}
				stats = (struct ng_source_stats *)resp->data;
				bcopy(&sc->stats, stats, sizeof(* stats));
                        }
                        if (msg->header.cmd != NGM_SOURCE_GET_STATS)
				bzero(&sc->stats, sizeof(sc->stats));
		    }
		    break;
		case NGM_SOURCE_START:
		    {
			uint64_t packets;

			if (msg->header.arglen != sizeof(uint64_t)) {
				error = EINVAL;
				break;
			}

			packets = *(uint64_t *)msg->data;

			error = ng_source_start(sc, packets);

		    	break;
		    }
		case NGM_SOURCE_STOP:
			ng_source_stop(sc);
			break;
		case NGM_SOURCE_CLR_DATA:
			ng_source_clr_data(sc);
			break;
		case NGM_SOURCE_SETIFACE:
		    {
			char *ifname = (char *)msg->data;

			if (msg->header.arglen < 2) {
				error = EINVAL;
				break;
			}

			ng_source_store_output_ifp(sc, ifname);
			break;
		    }
		case NGM_SOURCE_SETPPS:
		    {
			uint32_t pps;

			if (msg->header.arglen != sizeof(uint32_t)) {
				error = EINVAL;
				break;
			}

			pps = *(uint32_t *)msg->data;

			sc->stats.maxPps = pps;

			break;
		    }
		case NGM_SOURCE_SET_TIMESTAMP:
		    {
			struct ng_source_embed_info *embed;

			if (msg->header.arglen != sizeof(*embed)) {
				error = EINVAL;
				goto done;
			}
			embed = (struct ng_source_embed_info *)msg->data;
			bcopy(embed, &sc->embed_timestamp, sizeof(*embed));

			break;
		    }
		case NGM_SOURCE_GET_TIMESTAMP:
		    {
			struct ng_source_embed_info *embed;

			NG_MKRESPONSE(resp, msg, sizeof(*embed), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				goto done;
			}
			embed = (struct ng_source_embed_info *)resp->data;
			bcopy(&sc->embed_timestamp, embed, sizeof(*embed));

			break;
		    }
		case NGM_SOURCE_SET_COUNTER:
		    {
			struct ng_source_embed_cnt_info *embed;

			if (msg->header.arglen != sizeof(*embed)) {
				error = EINVAL;
				goto done;
			}
			embed = (struct ng_source_embed_cnt_info *)msg->data;
			if (embed->index >= NG_SOURCE_COUNTERS ||
			    !(embed->width == 1 || embed->width == 2 ||
			    embed->width == 4)) {
				error = EINVAL;
				goto done;
			}
			bcopy(embed, &sc->embed_counter[embed->index],
			    sizeof(*embed));

			break;
		    }
		case NGM_SOURCE_GET_COUNTER:
		    {
			uint8_t index = *(uint8_t *)msg->data;
			struct ng_source_embed_cnt_info *embed;

			if (index >= NG_SOURCE_COUNTERS) {
				error = EINVAL;
				goto done;
			}
			NG_MKRESPONSE(resp, msg, sizeof(*embed), M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				goto done;
			}
			embed = (struct ng_source_embed_cnt_info *)resp->data;
			bcopy(&sc->embed_counter[index], embed, sizeof(*embed));

			break;
		    }
		default:
			error = EINVAL;
			break;
		}
		break;
	case NGM_ETHER_COOKIE:
		if (!(msg->header.flags & NGF_RESP)) {
			error = EINVAL;
			break;
		}
		switch (msg->header.cmd) {
		case NGM_ETHER_GET_IFNAME:
		    {
			char *ifname = (char *)msg->data;

			if (msg->header.arglen < 2) {
				error = EINVAL;
				break;
			}

			if (ng_source_store_output_ifp(sc, ifname) == 0)
				ng_source_set_autosrc(sc, 0);
			break;
		    }
		default:
			error = EINVAL;
		}
		break;
	default:
		error = EINVAL;
		break;
	}

done:
	/* Take care of synchronous response, if any. */
	NG_RESPOND_MSG(error, node, item, resp);
	/* Free the message and return. */
	NG_FREE_MSG(msg);
	return (error);
}