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
typedef  int /*<<< orphan*/  hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */
 scalar_t__ HX509_NAME_MALFORMED ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 scalar_t__ hx509_parse_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
test_name_fail(hx509_context context, const char *name)
{
    hx509_name n;

    if (hx509_parse_name(context, name, &n) == HX509_NAME_MALFORMED)
	return 0;
    hx509_name_free(&n);
    return 1;
}