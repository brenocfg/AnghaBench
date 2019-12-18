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
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  hx509_context_free (int /*<<< orphan*/ *) ; 
 int hx509_context_init (int /*<<< orphan*/ *) ; 
 scalar_t__ test_compare (int /*<<< orphan*/ ) ; 
 scalar_t__ test_expand (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ test_name (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ test_name_fail (int /*<<< orphan*/ ,char*) ; 

int
main(int argc, char **argv)
{
    hx509_context context;
    int ret = 0;

    ret = hx509_context_init(&context);
    if (ret)
	errx(1, "hx509_context_init failed with %d", ret);

    ret += test_name(context, "CN=foo,C=SE");
    ret += test_name(context, "CN=foo,CN=kaka,CN=FOO,DC=ad1,C=SE");
    ret += test_name(context, "1.2.3.4=foo,C=SE");
    ret += test_name_fail(context, "=");
    ret += test_name_fail(context, "CN=foo,=foo");
    ret += test_name_fail(context, "CN=foo,really-unknown-type=foo");

    ret += test_expand(context, "UID=${uid},C=SE", "UID=lha,C=SE");
    ret += test_expand(context, "UID=foo${uid},C=SE", "UID=foolha,C=SE");
    ret += test_expand(context, "UID=${uid}bar,C=SE", "UID=lhabar,C=SE");
    ret += test_expand(context, "UID=f${uid}b,C=SE", "UID=flhab,C=SE");
    ret += test_expand(context, "UID=${uid}${uid},C=SE", "UID=lhalha,C=SE");
    ret += test_expand(context, "UID=${uid}{uid},C=SE", "UID=lha{uid},C=SE");

    ret += test_compare(context);

    hx509_context_free(&context);

    return ret;
}