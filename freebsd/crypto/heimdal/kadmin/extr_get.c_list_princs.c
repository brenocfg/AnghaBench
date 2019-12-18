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
struct list_options {int dummy; } ;
struct get_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int getit (struct get_options*,char*,int,char**) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*) ; 

int
list_princs(struct list_options *opt, int argc, char **argv)
{
    if(sizeof(struct get_options) != sizeof(struct list_options)) {
	krb5_warnx(context, "programmer error: sizeof(struct get_options) != sizeof(struct list_options)");
	return 0;
    }
    return getit((struct get_options*)opt, "list", argc, argv);
}