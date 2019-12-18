#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vdump_args {struct table_value* pval; } ;
struct table_value {int dummy; } ;
struct TYPE_2__ {size_t kidx; char* name; } ;
struct table_val_link {TYPE_1__ no; struct table_value* pval; } ;
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
update_tvalue(struct namedobj_instance *ni, struct named_object *no, void *arg)
{
	struct vdump_args *da;
	struct table_val_link *ptv;
	struct table_value *pval;

	da = (struct vdump_args *)arg;
	ptv = (struct table_val_link *)no;

	pval = da->pval;
	ptv->pval = &pval[ptv->no.kidx];
	ptv->no.name = (char *)&pval[ptv->no.kidx];
	return (0);
}