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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/ * krb5_const_principal ;
typedef  scalar_t__ krb5_boolean ;
struct TYPE_4__ {int /*<<< orphan*/  acl_file; } ;
struct TYPE_5__ {int /*<<< orphan*/  context; int /*<<< orphan*/  caller; TYPE_1__ config; } ;
typedef  TYPE_2__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ _kadm5_string_to_privs (char*,unsigned int*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_principal_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static kadm5_ret_t
fetch_acl (kadm5_server_context *context,
	   krb5_const_principal princ,
	   unsigned *ret_flags)
{
    FILE *f;
    krb5_error_code ret = 0;
    char buf[256];

    *ret_flags = 0;

    /* no acl file -> no rights */
    f = fopen(context->config.acl_file, "r");
    if (f == NULL)
	return 0;

    while(fgets(buf, sizeof(buf), f) != NULL) {
	char *foo = NULL, *p;
	krb5_principal this_princ;
	unsigned flags = 0;

	p = strtok_r(buf, " \t\n", &foo);
	if(p == NULL)
	    continue;
	if (*p == '#')		/* comment */
	    continue;
	ret = krb5_parse_name(context->context, p, &this_princ);
	if(ret)
	    break;
	if(!krb5_principal_compare(context->context,
				   context->caller, this_princ)) {
	    krb5_free_principal(context->context, this_princ);
	    continue;
	}
	krb5_free_principal(context->context, this_princ);
	p = strtok_r(NULL, " \t\n", &foo);
	if(p == NULL)
	    continue;
	ret = _kadm5_string_to_privs(p, &flags);
	if (ret)
	    break;
	p = strtok_r(NULL, " \t\n", &foo);
	if (p == NULL) {
	    *ret_flags = flags;
	    break;
	}
	if (princ != NULL) {
	    krb5_principal pattern_princ;
	    krb5_boolean match;

	    ret = krb5_parse_name (context->context, p, &pattern_princ);
	    if (ret)
		break;
	    match = krb5_principal_match (context->context,
					  princ, pattern_princ);
	    krb5_free_principal (context->context, pattern_princ);
	    if (match) {
		*ret_flags = flags;
		break;
	    }
	}
    }
    fclose(f);
    return ret;
}