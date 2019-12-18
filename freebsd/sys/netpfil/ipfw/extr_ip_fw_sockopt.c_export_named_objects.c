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
struct sockopt_data {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct dump_args {scalar_t__ tcount; int* bmask; } ;

/* Variables and functions */
 int IPFW_TABLES_MAX ; 
 int export_objhash_ntlv (struct namedobj_instance*,int,struct sockopt_data*) ; 

__attribute__((used)) static int
export_named_objects(struct namedobj_instance *ni, struct dump_args *da,
    struct sockopt_data *sd)
{
	int error, i;

	for (i = 0; i < IPFW_TABLES_MAX && da->tcount > 0; i++) {
		if ((da->bmask[i / 32] & (1 << (i % 32))) == 0)
			continue;
		if ((error = export_objhash_ntlv(ni, i, sd)) != 0)
			return (error);
		da->tcount--;
	}
	return (0);
}