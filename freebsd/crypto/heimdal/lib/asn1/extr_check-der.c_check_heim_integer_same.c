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
typedef  int /*<<< orphan*/  heim_integer ;

/* Variables and functions */
 int /*<<< orphan*/  der_free_heim_integer (int /*<<< orphan*/ *) ; 
 scalar_t__ der_heim_integer_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int der_parse_hex_heim_integer (char const*,int /*<<< orphan*/ *) ; 
 int der_print_hex_heim_integer (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
check_heim_integer_same(const char *p, const char *norm_p, heim_integer *i)
{
    heim_integer i2;
    char *str;
    int ret;

    ret = der_print_hex_heim_integer(i, &str);
    if (ret)
	errx(1, "der_print_hex_heim_integer: %d", ret);

    if (strcmp(str, norm_p) != 0)
	errx(1, "der_print_hex_heim_integer: %s != %s", str, p);

    ret = der_parse_hex_heim_integer(str, &i2);
    if (ret)
	errx(1, "der_parse_hex_heim_integer: %d", ret);

    if (der_heim_integer_cmp(i, &i2) != 0)
	errx(1, "der_heim_integer_cmp: p %s", p);

    der_free_heim_integer(&i2);
    free(str);

    ret = der_parse_hex_heim_integer(p, &i2);
    if (ret)
	errx(1, "der_parse_hex_heim_integer: %d", ret);

    if (der_heim_integer_cmp(i, &i2) != 0)
	errx(1, "der_heim_integer_cmp: norm");

    der_free_heim_integer(&i2);

    return 0;
}