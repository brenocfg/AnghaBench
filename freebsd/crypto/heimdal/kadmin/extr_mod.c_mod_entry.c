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
struct modify_options {int dummy; } ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  do_mod_entry ; 
 scalar_t__ foreach_principal (char*,int /*<<< orphan*/ ,char*,struct modify_options*) ; 

int
mod_entry(struct modify_options *opt, int argc, char **argv)
{
    krb5_error_code ret = 0;
    int i;

    for(i = 0; i < argc; i++) {
	ret = foreach_principal(argv[i], do_mod_entry, "mod", opt);
	if (ret)
	    break;
    }
    return ret != 0;
}