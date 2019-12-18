#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct ccuser {int dummy; } ;
typedef  struct ccuser ccport ;
struct ccnode {int /*<<< orphan*/  hook_cnt; int /*<<< orphan*/  data; void* manage; void* dump; } ;
struct cchook {int is_uni; struct ccuser* inst; void* hook; struct ccnode* node; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NG_CCATM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NG_HOOK_FORCE_QUEUE (void*) ; 
 int /*<<< orphan*/  NG_HOOK_NAME (void*) ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (void*,struct cchook*) ; 
 int /*<<< orphan*/  NG_HOOK_SET_RCVDATA (void*,int /*<<< orphan*/ ) ; 
 struct ccnode* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 struct ccuser* cc_port_create (int /*<<< orphan*/ ,struct cchook*,int /*<<< orphan*/ ) ; 
 struct ccuser* cc_user_create (int /*<<< orphan*/ ,struct cchook*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cchook*,int /*<<< orphan*/ ) ; 
 struct cchook* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_ccatm_rcvdump ; 
 int /*<<< orphan*/  ng_ccatm_rcvmanage ; 
 int /*<<< orphan*/  ng_ccatm_rcvuni ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
ng_ccatm_newhook(node_p node, hook_p hook, const char *name)
{
	struct ccnode *priv = NG_NODE_PRIVATE(node);
	struct ccport *port;
	struct ccuser *user;
	struct cchook *hd;
	u_long lport;
	char *end;

	if (strncmp(name, "uni", 3) == 0) {
		/*
		 * This is a UNI hook. Should be a new port.
		 */
		if (name[3] == '\0')
			return (EINVAL);
		lport = strtoul(name + 3, &end, 10);
		if (*end != '\0' || lport == 0 || lport > 0xffffffff)
			return (EINVAL);

		hd = malloc(sizeof(*hd), M_NG_CCATM, M_NOWAIT);
		if (hd == NULL)
			return (ENOMEM);
		hd->is_uni = 1;
		hd->node = priv;
		hd->hook = hook;

		port = cc_port_create(priv->data, hd, (u_int)lport);
		if (port == NULL) {
			free(hd, M_NG_CCATM);
			return (ENOMEM);
		}
		hd->inst = port;

		NG_HOOK_SET_PRIVATE(hook, hd);
		NG_HOOK_SET_RCVDATA(hook, ng_ccatm_rcvuni);
		NG_HOOK_FORCE_QUEUE(hook);

		priv->hook_cnt++;

		return (0);
	}

	if (strcmp(name, "dump") == 0) {
		priv->dump = hook;
		NG_HOOK_SET_RCVDATA(hook, ng_ccatm_rcvdump);
		return (0);
	}

	if (strcmp(name, "manage") == 0) {
		priv->manage = hook;
		NG_HOOK_SET_RCVDATA(hook, ng_ccatm_rcvmanage);
		return (0);
	}

	/*
	 * User hook
	 */
	hd = malloc(sizeof(*hd), M_NG_CCATM, M_NOWAIT);
	if (hd == NULL)
		return (ENOMEM);
	hd->is_uni = 0;
	hd->node = priv;
	hd->hook = hook;

	user = cc_user_create(priv->data, hd, NG_HOOK_NAME(hook));
	if (user == NULL) {
		free(hd, M_NG_CCATM);
		return (ENOMEM);
	}

	hd->inst = user;
	NG_HOOK_SET_PRIVATE(hook, hd);
	NG_HOOK_FORCE_QUEUE(hook);

	priv->hook_cnt++;

	return (0);
}