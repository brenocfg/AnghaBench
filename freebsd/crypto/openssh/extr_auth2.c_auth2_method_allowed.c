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
typedef  size_t u_int ;
struct TYPE_5__ {scalar_t__ num_auth_methods; } ;
struct TYPE_4__ {size_t num_auth_methods; int /*<<< orphan*/ * auth_methods; } ;
typedef  TYPE_1__ Authctxt ;

/* Variables and functions */
 scalar_t__ MATCH_NONE ; 
 scalar_t__ list_starts_with (int /*<<< orphan*/ ,char const*,char const*) ; 
 TYPE_2__ options ; 

int
auth2_method_allowed(Authctxt *authctxt, const char *method,
    const char *submethod)
{
	u_int i;

	/*
	 * NB. authctxt->num_auth_methods might be zero as a result of
	 * auth2_setup_methods_lists(), so check the configuration.
	 */
	if (options.num_auth_methods == 0)
		return 1;
	for (i = 0; i < authctxt->num_auth_methods; i++) {
		if (list_starts_with(authctxt->auth_methods[i], method,
		    submethod) != MATCH_NONE)
			return 1;
	}
	return 0;
}