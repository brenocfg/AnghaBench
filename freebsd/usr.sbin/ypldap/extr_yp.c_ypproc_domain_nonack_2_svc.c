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
struct svc_req {int dummy; } ;
typedef  int /*<<< orphan*/  domainname ;
typedef  scalar_t__ bool_t ;
struct TYPE_2__ {int /*<<< orphan*/  sc_domainname; } ;

/* Variables and functions */
 TYPE_1__* env ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool_t *
ypproc_domain_nonack_2_svc(domainname *arg, struct svc_req *req)
{
	static bool_t	res;
	
	if (strcmp(*arg, env->sc_domainname) != 0)
		return NULL;
	res = (bool_t)1;
	return (&res);
}