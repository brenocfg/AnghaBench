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
struct ng_tag_hookstat {char* thisHook; int /*<<< orphan*/  tag_len; } ;
struct ng_tag_hookout {char* thisHook; int /*<<< orphan*/  tag_len; } ;
struct ng_tag_hookin {char* thisHook; int /*<<< orphan*/  tag_len; } ;
struct TYPE_3__ {int typecookie; int const cmd; int arglen; } ;
struct ng_mesg {char* data; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/ * hook_p ;
typedef  TYPE_2__* hinfo_p ;
struct TYPE_4__ {struct ng_tag_hookstat stats; struct ng_tag_hookstat* out; struct ng_tag_hookstat* in; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  ERROUT (int) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_TAG_CLR_STATS 135 
#define  NGM_TAG_COOKIE 134 
#define  NGM_TAG_GETCLR_STATS 133 
#define  NGM_TAG_GET_HOOKIN 132 
#define  NGM_TAG_GET_HOOKOUT 131 
#define  NGM_TAG_GET_STATS 130 
#define  NGM_TAG_SET_HOOKIN 129 
#define  NGM_TAG_SET_HOOKOUT 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_HOOK_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int NG_TAG_HOOKIN_SIZE (int /*<<< orphan*/ ) ; 
 int NG_TAG_HOOKOUT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct ng_tag_hookstat*,char*,int) ; 
 int /*<<< orphan*/  bzero (struct ng_tag_hookstat*,int) ; 
 int /*<<< orphan*/ * ng_findhook (int /*<<< orphan*/ ,char*) ; 
 int ng_tag_setdata_in (int /*<<< orphan*/ *,struct ng_tag_hookstat* const) ; 
 int ng_tag_setdata_out (int /*<<< orphan*/ *,struct ng_tag_hookstat* const) ; 

__attribute__((used)) static int
ng_tag_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	struct ng_mesg *msg;
	struct ng_mesg *resp = NULL;
	int error = 0;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_TAG_COOKIE:
		switch (msg->header.cmd) {
		case NGM_TAG_SET_HOOKIN:
		    {
			struct ng_tag_hookin *const
			    hp = (struct ng_tag_hookin *)msg->data;
			hook_p hook;

			/* Sanity check. */
			if (msg->header.arglen < sizeof(*hp)
			    || msg->header.arglen !=
			    NG_TAG_HOOKIN_SIZE(hp->tag_len))
				ERROUT(EINVAL);

			/* Find hook. */
			if ((hook = ng_findhook(node, hp->thisHook)) == NULL)
				ERROUT(ENOENT);

			/* Set new tag values. */
			if ((error = ng_tag_setdata_in(hook, hp)) != 0)
				ERROUT(error);
			break;
		    }

		case NGM_TAG_SET_HOOKOUT:
		    {
			struct ng_tag_hookout *const
			    hp = (struct ng_tag_hookout *)msg->data;
			hook_p hook;

			/* Sanity check. */
			if (msg->header.arglen < sizeof(*hp)
			    || msg->header.arglen !=
			    NG_TAG_HOOKOUT_SIZE(hp->tag_len))
				ERROUT(EINVAL);

			/* Find hook. */
			if ((hook = ng_findhook(node, hp->thisHook)) == NULL)
				ERROUT(ENOENT);

			/* Set new tag values. */
			if ((error = ng_tag_setdata_out(hook, hp)) != 0)
				ERROUT(error);
			break;
		    }

		case NGM_TAG_GET_HOOKIN:
		    {
			struct ng_tag_hookin *hp;
			hook_p hook;

			/* Sanity check. */
			if (msg->header.arglen == 0)
				ERROUT(EINVAL);
			msg->data[msg->header.arglen - 1] = '\0';

			/* Find hook. */
			if ((hook = ng_findhook(node, msg->data)) == NULL)
				ERROUT(ENOENT);

			/* Build response. */
			hp = ((hinfo_p)NG_HOOK_PRIVATE(hook))->in;
			NG_MKRESPONSE(resp, msg,
			    NG_TAG_HOOKIN_SIZE(hp->tag_len), M_WAITOK);
			/* M_WAITOK can't return NULL. */
			bcopy(hp, resp->data,
			   NG_TAG_HOOKIN_SIZE(hp->tag_len));
			break;
		    }

		case NGM_TAG_GET_HOOKOUT:
		    {
			struct ng_tag_hookout *hp;
			hook_p hook;

			/* Sanity check. */
			if (msg->header.arglen == 0)
				ERROUT(EINVAL);
			msg->data[msg->header.arglen - 1] = '\0';

			/* Find hook. */
			if ((hook = ng_findhook(node, msg->data)) == NULL)
				ERROUT(ENOENT);

			/* Build response. */
			hp = ((hinfo_p)NG_HOOK_PRIVATE(hook))->out;
			NG_MKRESPONSE(resp, msg,
			    NG_TAG_HOOKOUT_SIZE(hp->tag_len), M_WAITOK);
			/* M_WAITOK can't return NULL. */
			bcopy(hp, resp->data,
			   NG_TAG_HOOKOUT_SIZE(hp->tag_len));
			break;
		    }

#ifdef NG_TAG_DEBUG
		case NGM_TAG_GET_STATS:
		case NGM_TAG_CLR_STATS:
		case NGM_TAG_GETCLR_STATS:
		    {
			struct ng_tag_hookstat *stats;
			hook_p hook;

			/* Sanity check. */
			if (msg->header.arglen == 0)
				ERROUT(EINVAL);
			msg->data[msg->header.arglen - 1] = '\0';

			/* Find hook. */
			if ((hook = ng_findhook(node, msg->data)) == NULL)
				ERROUT(ENOENT);
			stats = &((hinfo_p)NG_HOOK_PRIVATE(hook))->stats;

			/* Build response (if desired). */
			if (msg->header.cmd != NGM_TAG_CLR_STATS) {
				NG_MKRESPONSE(resp,
				    msg, sizeof(*stats), M_WAITOK);
				/* M_WAITOK can't return NULL. */
				bcopy(stats, resp->data, sizeof(*stats));
			}

			/* Clear stats (if desired). */
			if (msg->header.cmd != NGM_TAG_GET_STATS)
				bzero(stats, sizeof(*stats));
			break;
		    }
#endif /* NG_TAG_DEBUG */

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