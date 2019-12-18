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
 int /*<<< orphan*/  do_del_entry ; 
 scalar_t__ foreach_principal (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int
del_entry(void *opt, int argc, char **argv)
{
    int i;
    krb5_error_code ret = 0;

    for(i = 0; i < argc; i++) {
	ret = foreach_principal(argv[i], do_del_entry, "del", NULL);
	if (ret)
	    break;
    }
    return ret != 0;
}