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
struct indent_arg {int indent; } ;
struct devinfo_rman {char* dm_desc; } ;

/* Variables and functions */
 scalar_t__ devinfo_foreach_rman_resource (struct devinfo_rman*,int /*<<< orphan*/ ,struct indent_arg*) ; 
 int /*<<< orphan*/  print_device_matching_resource ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
print_device_rman_resources(struct devinfo_rman *rman, void *arg)
{
	struct indent_arg	*ia = (struct indent_arg *)arg;
	int			indent, i;

	indent = ia->indent;

	/* check whether there are any resources matching this device */
	ia->indent = 0;
	if (devinfo_foreach_rman_resource(rman,
	    print_device_matching_resource, ia) != 0) {

		/* there are, print header */
		for (i = 0; i < indent; i++)
			printf(" ");
		printf("%s:\n", rman->dm_desc);

		/* print resources */
		ia->indent = indent + 4;
		devinfo_foreach_rman_resource(rman,
		    print_device_matching_resource, ia);
	}
	ia->indent = indent;
	return(0);
}