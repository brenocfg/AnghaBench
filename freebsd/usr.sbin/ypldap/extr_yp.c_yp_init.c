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
struct yp_data {int /*<<< orphan*/ * yp_trans_tcp; int /*<<< orphan*/ * yp_trans_udp; int /*<<< orphan*/  yd_events; } ;
struct env {struct yp_data* sc_yp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  RPC_ANYSOCK ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  YPPROG ; 
 int /*<<< orphan*/  YPVERS ; 
 struct yp_data* calloc (int,int) ; 
 struct env* env ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  pmap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svctcp_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svcudp_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yp_dispatch ; 

void
yp_init(struct env *x_env)
{
	struct yp_data	*yp;

	if ((yp = calloc(1, sizeof(*yp))) == NULL)
		fatal(NULL);
	TAILQ_INIT(&yp->yd_events);

	env = x_env;
	env->sc_yp = yp;
	
	(void)pmap_unset(YPPROG, YPVERS);

	if ((yp->yp_trans_udp = svcudp_create(RPC_ANYSOCK)) == NULL)
		fatal("cannot create udp service");
	if ((yp->yp_trans_tcp = svctcp_create(RPC_ANYSOCK, 0, 0)) == NULL)
		fatal("cannot create tcp service");

	if (!svc_register(yp->yp_trans_udp, YPPROG, YPVERS,
	    yp_dispatch, IPPROTO_UDP)) {
		fatal("unable to register (YPPROG, YPVERS, udp)");
	}
	if (!svc_register(yp->yp_trans_tcp, YPPROG, YPVERS,
	    yp_dispatch, IPPROTO_TCP)) {
		fatal("unable to register (YPPROG, YPVERS, tcp)");
	}
}