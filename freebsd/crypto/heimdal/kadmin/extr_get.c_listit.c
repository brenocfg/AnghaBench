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

/* Variables and functions */
 int /*<<< orphan*/  do_list_entry ; 
 scalar_t__ foreach_principal (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
listit(const char *funcname, int argc, char **argv)
{
    int i;
    krb5_error_code ret, saved_ret = 0;

    for (i = 0; i < argc; i++) {
	ret = foreach_principal(argv[i], do_list_entry, funcname, NULL);
        if (saved_ret == 0 && ret != 0)
            saved_ret = ret;
    }
    return saved_ret != 0;
}