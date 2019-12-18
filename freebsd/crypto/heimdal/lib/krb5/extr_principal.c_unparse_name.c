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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_principal ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 scalar_t__ princ_ncomp (int /*<<< orphan*/ ,size_t) ; 
 size_t princ_num_comp (int /*<<< orphan*/ ) ; 
 scalar_t__ princ_realm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quotable_chars ; 
 size_t strcspn (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t strlen (scalar_t__) ; 
 scalar_t__ unparse_name_fixed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int) ; 

__attribute__((used)) static krb5_error_code
unparse_name(krb5_context context,
	     krb5_const_principal principal,
	     char **name,
	     int flags)
{
    size_t len = 0, plen;
    size_t i;
    krb5_error_code ret;
    /* count length */
    if (princ_realm(principal)) {
	plen = strlen(princ_realm(principal));

	if(strcspn(princ_realm(principal), quotable_chars) == plen)
	    len += plen;
	else
	    len += 2*plen;
	len++; /* '@' */
    }
    for(i = 0; i < princ_num_comp(principal); i++){
	plen = strlen(princ_ncomp(principal, i));
	if(strcspn(princ_ncomp(principal, i), quotable_chars) == plen)
	    len += plen;
	else
	    len += 2*plen;
	len++;
    }
    len++; /* '\0' */
    *name = malloc(len);
    if(*name == NULL) {
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    ret = unparse_name_fixed(context, principal, *name, len, flags);
    if(ret) {
	free(*name);
	*name = NULL;
    }
    return ret;
}