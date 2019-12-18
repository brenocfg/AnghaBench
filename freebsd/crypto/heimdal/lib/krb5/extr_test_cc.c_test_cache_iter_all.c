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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_cccol_cursor ;
typedef  int /*<<< orphan*/ * krb5_ccache ;

/* Variables and functions */
 scalar_t__ debug_flag ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* krb5_cc_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cccol_cursor_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cccol_cursor_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cccol_cursor_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
test_cache_iter_all(krb5_context context)
{
    krb5_cccol_cursor cursor;
    krb5_error_code ret;
    krb5_ccache id;

    ret = krb5_cccol_cursor_new (context, &cursor);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cccol_cursor_new");


    while ((ret = krb5_cccol_cursor_next (context, cursor, &id)) == 0 && id != NULL) {
	krb5_principal principal;
	char *name;

	if (debug_flag)
	    printf("name: %s\n", krb5_cc_get_name(context, id));
	ret = krb5_cc_get_principal(context, id, &principal);
	if (ret == 0) {
	    ret = krb5_unparse_name(context, principal, &name);
	    if (ret == 0) {
		if (debug_flag)
		    printf("\tprincipal: %s\n", name);
		free(name);
	    }
	    krb5_free_principal(context, principal);
	}
	krb5_cc_close(context, id);
    }

    krb5_cccol_cursor_free(context, &cursor);
}