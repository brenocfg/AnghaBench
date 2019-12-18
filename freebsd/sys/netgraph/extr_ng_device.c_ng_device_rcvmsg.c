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
struct TYPE_4__ {scalar_t__ typecookie; int cmd; } ;
struct ng_mesg {scalar_t__ data; TYPE_1__ header; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_5__ {int /*<<< orphan*/  ngddev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERROUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 scalar_t__ NGM_DEVICE_COOKIE ; 
#define  NGM_DEVICE_GET_DEVNAME 128 
 char const* NG_DEVICE_DEVNAME ; 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 char* devtoname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
ng_device_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_mesg *msg;
	struct ng_mesg *resp = NULL;
	const char *dn;
	int error = 0;

	NGI_GET_MSG(item, msg);

	if (msg->header.typecookie == NGM_DEVICE_COOKIE) {
		switch (msg->header.cmd) {
		case NGM_DEVICE_GET_DEVNAME:
			/* XXX: Fix when MAX_NGD us bigger */
			NG_MKRESPONSE(resp, msg,
			    strlen(NG_DEVICE_DEVNAME) + 4, M_NOWAIT);

			if (resp == NULL)
				ERROUT(ENOMEM);

			dn = devtoname(priv->ngddev);
			strlcpy((char *)resp->data, dn, strlen(dn) + 1);
			break;

		default:
			error = EINVAL;
			break;
		}
	} else
		error = EINVAL;

done:
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);
	return (error);
}