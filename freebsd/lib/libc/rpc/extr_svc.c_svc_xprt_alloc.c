#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * svc_ah_ops; } ;
struct TYPE_9__ {TYPE_1__ xp_auth; struct TYPE_9__* xp_p3; } ;
typedef  TYPE_2__ SVCXPRT_EXT ;
typedef  TYPE_2__ SVCXPRT ;

/* Variables and functions */
 TYPE_2__* mem_alloc (int) ; 
 int /*<<< orphan*/  mem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svc_auth_null_ops ; 

SVCXPRT *
svc_xprt_alloc(void)
{
	SVCXPRT *xprt;
	SVCXPRT_EXT *ext;

	xprt = mem_alloc(sizeof(SVCXPRT));
	if (xprt == NULL)
		return (NULL);
	memset(xprt, 0, sizeof(SVCXPRT));
	ext = mem_alloc(sizeof(SVCXPRT_EXT));
	if (ext == NULL) {
		mem_free(xprt, sizeof(SVCXPRT));
		return (NULL);
	}
	memset(ext, 0, sizeof(SVCXPRT_EXT));
	xprt->xp_p3 = ext;
	ext->xp_auth.svc_ah_ops = &svc_auth_null_ops;

	return (xprt);
}