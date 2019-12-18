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
struct TYPE_4__ {int /*<<< orphan*/  yp_buf_val; int /*<<< orphan*/  yp_buf_len; } ;
struct ypdelete_args {TYPE_2__ key; int /*<<< orphan*/  mapname; } ;
struct svc_req {scalar_t__ rq_clntcred; int /*<<< orphan*/  rq_xprt; } ;
struct TYPE_3__ {char* name; } ;
struct authdes_cred {TYPE_1__ adc_fullname; } ;
typedef  enum auth_stat { ____Placeholder_auth_stat } auth_stat ;

/* Variables and functions */
 int AUTH_OK ; 
 int /*<<< orphan*/  YPOP_DELETE ; 
 int localupdate (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcerr_auth (int /*<<< orphan*/ ,int) ; 
 int yp_checkauth (struct svc_req*) ; 
 int ypmap_update (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

unsigned int *
ypu_delete_1_svc(struct ypdelete_args *args, struct svc_req *svcreq)
{
	struct authdes_cred *des_cred;
	static int res;
	char *netname;
	enum auth_stat astat;

	res = 0;

	astat = yp_checkauth(svcreq);

	if (astat != AUTH_OK) {
		svcerr_auth(svcreq->rq_xprt, astat);
		return(&res);
	}

	des_cred = (struct authdes_cred *) svcreq->rq_clntcred;
	netname = des_cred->adc_fullname.name;

	res = localupdate(netname, "/etc/publickey", YPOP_DELETE,
		args->key.yp_buf_len, args->key.yp_buf_val,
		0,			NULL);

	if (res)
		return (&res);

	res = ypmap_update(netname, args->mapname, YPOP_DELETE,
		args->key.yp_buf_len, args->key.yp_buf_val,
		0,			NULL);

	return (&res);
}