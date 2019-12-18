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
typedef  int /*<<< orphan*/  krb5_realm ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_principal ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int KRB5_PRINCIPAL_UNPARSE_DISPLAY ; 
 int KRB5_PRINCIPAL_UNPARSE_NO_REALM ; 
 int KRB5_PRINCIPAL_UNPARSE_SHORT ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  add_char (char*,size_t,size_t,char) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_get_default_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * princ_ncomp (int /*<<< orphan*/ ,size_t) ; 
 size_t princ_num_comp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * princ_realm (int /*<<< orphan*/ ) ; 
 size_t quote_string (int /*<<< orphan*/ *,char*,size_t,size_t,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
unparse_name_fixed(krb5_context context,
		   krb5_const_principal principal,
		   char *name,
		   size_t len,
		   int flags)
{
    size_t idx = 0;
    size_t i;
    int short_form = (flags & KRB5_PRINCIPAL_UNPARSE_SHORT) != 0;
    int no_realm = (flags & KRB5_PRINCIPAL_UNPARSE_NO_REALM) != 0;
    int display = (flags & KRB5_PRINCIPAL_UNPARSE_DISPLAY) != 0;

    if (!no_realm && princ_realm(principal) == NULL) {
	krb5_set_error_message(context, ERANGE,
			       N_("Realm missing from principal, "
				  "can't unparse", ""));
	return ERANGE;
    }

    for(i = 0; i < princ_num_comp(principal); i++){
	if(i)
	    add_char(name, idx, len, '/');
	idx = quote_string(princ_ncomp(principal, i), name, idx, len, display);
	if(idx == len) {
	    krb5_set_error_message(context, ERANGE,
				   N_("Out of space printing principal", ""));
	    return ERANGE;
	}
    }
    /* add realm if different from default realm */
    if(short_form && !no_realm) {
	krb5_realm r;
	krb5_error_code ret;
	ret = krb5_get_default_realm(context, &r);
	if(ret)
	    return ret;
	if(strcmp(princ_realm(principal), r) != 0)
	    short_form = 0;
	free(r);
    }
    if(!short_form && !no_realm) {
	add_char(name, idx, len, '@');
	idx = quote_string(princ_realm(principal), name, idx, len, display);
	if(idx == len) {
	    krb5_set_error_message(context, ERANGE,
				   N_("Out of space printing "
				      "realm of principal", ""));
	    return ERANGE;
	}
    }
    return 0;
}