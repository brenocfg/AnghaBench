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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ret_string_xdr (int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static int
ret_principal_xdr(krb5_context contextp,
		  krb5_storage *sp,
		  krb5_principal *p)
{
    char *str;
    *p = NULL;
    CHECK(ret_string_xdr(sp, &str));
    if (str) {
	CHECK(krb5_parse_name(contextp, str, p));
	free(str);
    }
    return 0;
}