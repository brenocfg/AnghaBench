#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockopt {scalar_t__ sopt_dir; int sopt_name; int sopt_valsize; TYPE_1__* sopt_td; } ;
struct dn_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int) ; 
 int EINVAL ; 
#define  IP_DUMMYNET3 132 
#define  IP_DUMMYNET_CONFIGURE 131 
#define  IP_DUMMYNET_DEL 130 
#define  IP_DUMMYNET_FLUSH 129 
#define  IP_DUMMYNET_GET 128 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PRIV_NETINET_DUMMYNET ; 
 scalar_t__ SOPT_GET ; 
 scalar_t__ SOPT_SET ; 
 int do_config (void*,int) ; 
 int dummynet_get (struct sockopt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int ip_dummynet_compat (struct sockopt*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int priv_check (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int securelevel_ge (int /*<<< orphan*/ ,int) ; 
 int sooptcopyin (struct sockopt*,void*,int,int) ; 

__attribute__((used)) static int
ip_dn_ctl(struct sockopt *sopt)
{
	void *p = NULL;
	int error, l;

	error = priv_check(sopt->sopt_td, PRIV_NETINET_DUMMYNET);
	if (error)
		return (error);

	/* Disallow sets in really-really secure mode. */
	if (sopt->sopt_dir == SOPT_SET) {
		error =  securelevel_ge(sopt->sopt_td->td_ucred, 3);
		if (error)
			return (error);
	}

	switch (sopt->sopt_name) {
	default :
		D("dummynet: unknown option %d", sopt->sopt_name);
		error = EINVAL;
		break;

	case IP_DUMMYNET_FLUSH:
	case IP_DUMMYNET_CONFIGURE:
	case IP_DUMMYNET_DEL:	/* remove a pipe or queue */
	case IP_DUMMYNET_GET:
		D("dummynet: compat option %d", sopt->sopt_name);
		error = ip_dummynet_compat(sopt);
		break;

	case IP_DUMMYNET3 :
		if (sopt->sopt_dir == SOPT_GET) {
			error = dummynet_get(sopt, NULL);
			break;
		}
		l = sopt->sopt_valsize;
		if (l < sizeof(struct dn_id) || l > 12000) {
			D("argument len %d invalid", l);
			break;
		}
		p = malloc(l, M_TEMP, M_WAITOK); // XXX can it fail ?
		error = sooptcopyin(sopt, p, l, l);
		if (error)
			break ;
		error = do_config(p, l);
		break;
	}

	if (p != NULL)
		free(p, M_TEMP);

	return error ;
}