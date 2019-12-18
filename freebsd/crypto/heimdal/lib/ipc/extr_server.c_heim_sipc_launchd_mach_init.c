#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mach_port_t ;
typedef  TYPE_1__* heim_sipc ;
typedef  int /*<<< orphan*/  heim_ipc_callback ;
struct TYPE_6__ {int /*<<< orphan*/  callback; void* userctx; int /*<<< orphan*/  release; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_RECEIVE ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ mach_checkin_or_register (char const*) ; 
 int mach_init (char const*,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  mach_port_mod_refs (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mach_release ; 
 int /*<<< orphan*/  mach_task_self () ; 

int
heim_sipc_launchd_mach_init(const char *service,
			    heim_ipc_callback callback,
			    void *user, heim_sipc *ctx)
{
#if defined(__APPLE__) && defined(HAVE_GCD)
    mach_port_t sport = MACH_PORT_NULL;
    heim_sipc c = NULL;
    int ret;

    *ctx = NULL;

    sport = mach_checkin_or_register(service);
    if (sport == MACH_PORT_NULL) {
	ret = ENOENT;
	goto error;
    }

    c = calloc(1, sizeof(*c));
    if (c == NULL) {
	ret = ENOMEM;
	goto error;
    }
    c->release = mach_release;
    c->userctx = user;
    c->callback = callback;

    ret = mach_init(service, sport, c);
    if (ret)
	goto error;

    *ctx = c;
    return 0;
 error:
    if (c)
	free(c);
    if (sport != MACH_PORT_NULL)
	mach_port_mod_refs(mach_task_self(), sport,
			   MACH_PORT_RIGHT_RECEIVE, -1);
    return ret;
#else /* !(__APPLE__ && HAVE_GCD) */
    *ctx = NULL;
    return EINVAL;
#endif /* __APPLE__ && HAVE_GCD */
}