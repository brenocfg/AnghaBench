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
typedef  scalar_t__ krb5_context ;
typedef  int /*<<< orphan*/  PTYPE ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  krb5_set_error_message (scalar_t__,int,char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static int
_expand_null(krb5_context context, PTYPE param, const char *postfix, char **ret)
{
    *ret = strdup("");
    if (*ret == NULL) {
	if (context)
	    krb5_set_error_message(context, ENOMEM, "Out of memory");
	return ENOMEM;
    }
    return 0;
}