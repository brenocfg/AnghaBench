#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
struct _table_value {int spare1; scalar_t__ refcnt; } ;
typedef  int /*<<< orphan*/  ipfw_table_value ;
struct TYPE_4__ {int count; scalar_t__ objsize; } ;
typedef  TYPE_1__ ipfw_obj_lheader ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  compare_values ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  qsort (struct _table_value*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int table_do_get_vlist (TYPE_1__**) ; 
 int /*<<< orphan*/  table_print_valheader (char*,int,int) ; 
 int /*<<< orphan*/  table_show_value (char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
ipfw_list_values(int ac, char *av[])
{
	ipfw_obj_lheader *olh;
	struct _table_value *v;
	int error, i;
	uint32_t vmask;
	char buf[128];

	error = table_do_get_vlist(&olh);
	if (error != 0)
		err(EX_OSERR, "Unable to request value list");

	vmask = 0x7FFFFFFF; /* Similar to IPFW_VTYPE_LEGACY */

	table_print_valheader(buf, sizeof(buf), vmask);
	printf("HEADER: %s\n", buf);
	v = (struct _table_value *)(olh + 1);
	qsort(v, olh->count, olh->objsize, compare_values);
	for (i = 0; i < olh->count; i++) {
		table_show_value(buf, sizeof(buf), (ipfw_table_value *)v,
		    vmask, 0);
		printf("[%u] refs=%lu %s\n", v->spare1, (u_long)v->refcnt, buf);
		v = (struct _table_value *)((caddr_t)v + olh->objsize);
	}

	free(olh);
}