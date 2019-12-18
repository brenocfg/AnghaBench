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
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 char* TEST_CC_NAME ; 
 char* estrdup (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* krb5_cc_default_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_cc_set_default_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static void
test_default_name(krb5_context context)
{
    krb5_error_code ret;
    const char *p, *test_cc_name = TEST_CC_NAME;
    char *p1, *p2, *p3;

    p = krb5_cc_default_name(context);
    if (p == NULL)
	krb5_errx (context, 1, "krb5_cc_default_name 1 failed");
    p1 = estrdup(p);

    ret = krb5_cc_set_default_name(context, NULL);
    if (p == NULL)
	krb5_errx (context, 1, "krb5_cc_set_default_name failed");

    p = krb5_cc_default_name(context);
    if (p == NULL)
	krb5_errx (context, 1, "krb5_cc_default_name 2 failed");
    p2 = estrdup(p);

    if (strcmp(p1, p2) != 0)
	krb5_errx (context, 1, "krb5_cc_default_name no longer same");

    ret = krb5_cc_set_default_name(context, test_cc_name);
    if (p == NULL)
	krb5_errx (context, 1, "krb5_cc_set_default_name 1 failed");

    p = krb5_cc_default_name(context);
    if (p == NULL)
	krb5_errx (context, 1, "krb5_cc_default_name 2 failed");
    p3 = estrdup(p);

#ifndef KRB5_USE_PATH_TOKENS
    /* If we are using path tokens, we don't expect the p3 and
       test_cc_name to match since p3 is going to have expanded
       tokens. */
    if (strcmp(p3, test_cc_name) != 0)
	krb5_errx (context, 1, "krb5_cc_set_default_name 1 failed");
#endif

    free(p1);
    free(p2);
    free(p3);
}