#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* krb5_context ;
struct TYPE_3__ {int /*<<< orphan*/ * default_cc_name_env; scalar_t__ default_cc_name; scalar_t__ default_cc_name_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 scalar_t__ issuid () ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static int
environment_changed(krb5_context context)
{
    const char *e;

    /* if the cc name was set, don't change it */
    if (context->default_cc_name_set)
	return 0;

    /* XXX performance: always ask KCM/API if default name has changed */
    if (context->default_cc_name &&
	(strncmp(context->default_cc_name, "KCM:", 4) == 0 ||
	 strncmp(context->default_cc_name, "API:", 4) == 0))
	return 1;

    if(issuid())
	return 0;

    e = getenv("KRB5CCNAME");
    if (e == NULL) {
	if (context->default_cc_name_env) {
	    free(context->default_cc_name_env);
	    context->default_cc_name_env = NULL;
	    return 1;
	}
    } else {
	if (context->default_cc_name_env == NULL)
	    return 1;
	if (strcmp(e, context->default_cc_name_env) != 0)
	    return 1;
    }
    return 0;
}