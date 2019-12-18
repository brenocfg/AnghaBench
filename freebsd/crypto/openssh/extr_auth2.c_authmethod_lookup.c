#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* enabled; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Authmethod ;
typedef  int /*<<< orphan*/  Authctxt ;

/* Variables and functions */
 scalar_t__ auth2_method_allowed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__** authmethods ; 
 int /*<<< orphan*/  debug2 (char*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Authmethod *
authmethod_lookup(Authctxt *authctxt, const char *name)
{
	int i;

	if (name != NULL)
		for (i = 0; authmethods[i] != NULL; i++)
			if (authmethods[i]->enabled != NULL &&
			    *(authmethods[i]->enabled) != 0 &&
			    strcmp(name, authmethods[i]->name) == 0 &&
			    auth2_method_allowed(authctxt,
			    authmethods[i]->name, NULL))
				return authmethods[i];
	debug2("Unrecognized authentication method name: %s",
	    name ? name : "NULL");
	return NULL;
}