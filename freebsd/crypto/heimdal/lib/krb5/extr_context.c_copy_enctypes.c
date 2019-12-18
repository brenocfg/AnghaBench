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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  scalar_t__ krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC (scalar_t__*,size_t) ; 
 scalar_t__ KRB5_ENCTYPE_NULL ; 
 int /*<<< orphan*/  KRB5_PROG_ETYPE_NOSUPP ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ krb5_enctype_valid (int /*<<< orphan*/ ,scalar_t__ const) ; 
 int /*<<< orphan*/  krb5_enomem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
copy_enctypes(krb5_context context,
	      const krb5_enctype *in,
	      krb5_enctype **out)
{
    krb5_enctype *p = NULL;
    size_t m, n;

    for (n = 0; in[n]; n++)
	;
    n++;
    ALLOC(p, n);
    if(p == NULL)
	return krb5_enomem(context);
    for (n = 0, m = 0; in[n]; n++) {
	if (krb5_enctype_valid(context, in[n]) != 0)
	    continue;
	p[m++] = in[n];
    }
    p[m] = KRB5_ENCTYPE_NULL;
    if (m == 0) {
	free(p);
	krb5_set_error_message (context, KRB5_PROG_ETYPE_NOSUPP,
				N_("no valid enctype set", ""));
	return KRB5_PROG_ETYPE_NOSUPP;
    }
    *out = p;
    return 0;
}