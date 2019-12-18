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
struct vdump_args {int error; int /*<<< orphan*/  sd; } ;
struct table_value {int /*<<< orphan*/  spare1; } ;
struct TYPE_2__ {int /*<<< orphan*/  kidx; } ;
struct table_val_link {TYPE_1__ no; int /*<<< orphan*/  pval; } ;
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ipfw_get_sopt_space (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct table_value*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dump_tvalue(struct namedobj_instance *ni, struct named_object *no, void *arg)
{
	struct vdump_args *da;
	struct table_val_link *ptv;
	struct table_value *v;

	da = (struct vdump_args *)arg;
	ptv = (struct table_val_link *)no;

	v = (struct table_value *)ipfw_get_sopt_space(da->sd, sizeof(*v));
	/* Out of memory, returning */
	if (v == NULL) {
		da->error = ENOMEM;
		return (ENOMEM);
	}

	memcpy(v, ptv->pval, sizeof(*v));
	v->spare1 = ptv->no.kidx;
	return (0);
}