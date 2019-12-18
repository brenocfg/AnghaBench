#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct proc {int p_flag; } ;
struct TYPE_5__ {int typecookie; int arglen; int /*<<< orphan*/  cmd; } ;
struct ng_mesg {scalar_t__ data; TYPE_1__ header; } ;
typedef  TYPE_2__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_6__ {int hotchar; int /*<<< orphan*/ * tp; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERROUT (int /*<<< orphan*/ ) ; 
 int ESRCH ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
#define  NGM_TTY_COOKIE 131 
#define  NGM_TTY_GET_HOTCHAR 130 
#define  NGM_TTY_SET_HOTCHAR 129 
#define  NGM_TTY_SET_TTY 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int /*<<< orphan*/  PRELE (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_WEXIT ; 
 int /*<<< orphan*/  _PHOLD (struct proc*) ; 
 int /*<<< orphan*/  ngt_hook ; 
 struct proc* pfind (int) ; 
 int ttyhook_register (int /*<<< orphan*/ **,struct proc*,int,int /*<<< orphan*/ *,TYPE_2__* const) ; 

__attribute__((used)) static int
ngt_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	struct proc *p;
	const sc_p sc = NG_NODE_PRIVATE(node);
	struct ng_mesg *msg, *resp = NULL;
	int error = 0;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_TTY_COOKIE:
		switch (msg->header.cmd) {
		case NGM_TTY_SET_TTY:
			if (sc->tp != NULL)
				return (EBUSY);
			
			p = pfind(((int *)msg->data)[0]);
			if (p == NULL || (p->p_flag & P_WEXIT))
				return (ESRCH);
			_PHOLD(p);
			PROC_UNLOCK(p);
			error = ttyhook_register(&sc->tp, p, ((int *)msg->data)[1],
			    &ngt_hook, sc);
			PRELE(p);
			if (error != 0)
				return (error);
			break;
		case NGM_TTY_SET_HOTCHAR:
		    {
			int     hotchar;

			if (msg->header.arglen != sizeof(int))
				ERROUT(EINVAL);
			hotchar = *((int *) msg->data);
			if (hotchar != (u_char) hotchar && hotchar != -1)
				ERROUT(EINVAL);
			sc->hotchar = hotchar;	/* race condition is OK */
			break;
		    }
		case NGM_TTY_GET_HOTCHAR:
			NG_MKRESPONSE(resp, msg, sizeof(int), M_NOWAIT);
			if (!resp)
				ERROUT(ENOMEM);
			/* Race condition here is OK */
			*((int *) resp->data) = sc->hotchar;
			break;
		default:
			ERROUT(EINVAL);
		}
		break;
	default:
		ERROUT(EINVAL);
	}
done:
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);
	return (error);
}