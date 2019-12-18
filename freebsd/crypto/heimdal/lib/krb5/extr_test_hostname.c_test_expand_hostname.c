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
typedef  int /*<<< orphan*/  tests ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 scalar_t__ expand_hostname (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
test_expand_hostname(krb5_context context)
{
    int i, errors = 0;

    struct t {
	krb5_error_code ret;
	const char *orig_hostname;
	const char *new_hostname;
    } tests[] = {
	{ 0, "pstn1.su.se", "pstn1.su.se" },
	{ 0, "pstnproxy.su.se", "pstnproxy.su.se" },
    };

    for (i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
	errors += expand_hostname(context, tests[i].orig_hostname);
    }

    return errors;
}