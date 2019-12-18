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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 int hx509_name_to_string (int /*<<< orphan*/ ,char**) ; 
 int hx509_parse_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
test_name(hx509_context context, const char *name)
{
    hx509_name n;
    char *s;
    int ret;

    ret = hx509_parse_name(context, name, &n);
    if (ret)
	return 1;

    ret = hx509_name_to_string(n, &s);
    if (ret)
	return 1;

    if (strcmp(s, name) != 0)
	return 1;

    hx509_name_free(&n);
    free(s);

    return 0;
}