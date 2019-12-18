#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int typecookie; int const cmd; int arglen; } ;
struct ng_mesg {char* data; TYPE_1__ header; } ;
struct ng_bpf_hookstat {char* thisHook; int /*<<< orphan*/  bpf_prog_len; } ;
struct ng_bpf_hookprog {char* thisHook; int /*<<< orphan*/  bpf_prog_len; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/ * hook_p ;
typedef  TYPE_2__* hinfo_p ;
struct TYPE_4__ {struct ng_bpf_hookstat stats; struct ng_bpf_hookstat* prog; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROUT (int) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_BPF_CLR_STATS 133 
#define  NGM_BPF_COOKIE 132 
#define  NGM_BPF_GETCLR_STATS 131 
#define  NGM_BPF_GET_PROGRAM 130 
#define  NGM_BPF_GET_STATS 129 
#define  NGM_BPF_SET_PROGRAM 128 
 int NG_BPF_HOOKPROG_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_HOOK_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  bcopy (struct ng_bpf_hookstat*,char*,int) ; 
 int /*<<< orphan*/  bzero (struct ng_bpf_hookstat*,int) ; 
 int ng_bpf_setprog (int /*<<< orphan*/ *,struct ng_bpf_hookstat* const) ; 
 int /*<<< orphan*/ * ng_findhook (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ng_bpf_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	struct ng_mesg *msg;
	struct ng_mesg *resp = NULL;
	int error = 0;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_BPF_COOKIE:
		switch (msg->header.cmd) {
		case NGM_BPF_SET_PROGRAM:
		    {
			struct ng_bpf_hookprog *const
			    hp = (struct ng_bpf_hookprog *)msg->data;
			hook_p hook;

			/* Sanity check */
			if (msg->header.arglen < sizeof(*hp)
			    || msg->header.arglen
			      != NG_BPF_HOOKPROG_SIZE(hp->bpf_prog_len))
				ERROUT(EINVAL);

			/* Find hook */
			if ((hook = ng_findhook(node, hp->thisHook)) == NULL)
				ERROUT(ENOENT);

			/* Set new program */
			if ((error = ng_bpf_setprog(hook, hp)) != 0)
				ERROUT(error);
			break;
		    }

		case NGM_BPF_GET_PROGRAM:
		    {
			struct ng_bpf_hookprog *hp;
			hook_p hook;

			/* Sanity check */
			if (msg->header.arglen == 0)
				ERROUT(EINVAL);
			msg->data[msg->header.arglen - 1] = '\0';

			/* Find hook */
			if ((hook = ng_findhook(node, msg->data)) == NULL)
				ERROUT(ENOENT);

			/* Build response */
			hp = ((hinfo_p)NG_HOOK_PRIVATE(hook))->prog;
			NG_MKRESPONSE(resp, msg,
			    NG_BPF_HOOKPROG_SIZE(hp->bpf_prog_len), M_NOWAIT);
			if (resp == NULL)
				ERROUT(ENOMEM);
			bcopy(hp, resp->data,
			   NG_BPF_HOOKPROG_SIZE(hp->bpf_prog_len));
			break;
		    }

		case NGM_BPF_GET_STATS:
		case NGM_BPF_CLR_STATS:
		case NGM_BPF_GETCLR_STATS:
		    {
			struct ng_bpf_hookstat *stats;
			hook_p hook;

			/* Sanity check */
			if (msg->header.arglen == 0)
				ERROUT(EINVAL);
			msg->data[msg->header.arglen - 1] = '\0';

			/* Find hook */
			if ((hook = ng_findhook(node, msg->data)) == NULL)
				ERROUT(ENOENT);
			stats = &((hinfo_p)NG_HOOK_PRIVATE(hook))->stats;

			/* Build response (if desired) */
			if (msg->header.cmd != NGM_BPF_CLR_STATS) {
				NG_MKRESPONSE(resp,
				    msg, sizeof(*stats), M_NOWAIT);
				if (resp == NULL)
					ERROUT(ENOMEM);
				bcopy(stats, resp->data, sizeof(*stats));
			}

			/* Clear stats (if desired) */
			if (msg->header.cmd != NGM_BPF_GET_STATS)
				bzero(stats, sizeof(*stats));
			break;
		    }

		default:
			error = EINVAL;
			break;
		}
		break;
	default:
		error = EINVAL;
		break;
	}
done:
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);
	return (error);
}