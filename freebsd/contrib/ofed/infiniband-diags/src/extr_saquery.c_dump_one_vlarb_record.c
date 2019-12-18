#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct query_params {int dummy; } ;
struct TYPE_4__ {TYPE_3__* vl_entry; } ;
struct TYPE_5__ {int port_num; int block_num; int /*<<< orphan*/  lid; TYPE_1__ vl_arb_tbl; } ;
typedef  TYPE_2__ ib_vl_arb_table_record_t ;
struct TYPE_6__ {int vl; int weight; } ;
typedef  TYPE_3__ ib_vl_arb_element_t ;

/* Variables and functions */
 int cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,...) ; 

__attribute__((used)) static void dump_one_vlarb_record(void *data, struct query_params *p)
{
	ib_vl_arb_table_record_t *vlarb = data;
	ib_vl_arb_element_t *e = vlarb->vl_arb_tbl.vl_entry;
	int i;
	printf("VLArbTableRecord dump:\n"
	       "\t\tLID........................%u\n"
	       "\t\tPort.......................%u\n"
	       "\t\tBlock......................%u\n",
	       cl_ntoh16(vlarb->lid), vlarb->port_num, vlarb->block_num);
	for (i = 0; i < 32; i += 16)
		printf("\t\tVL    :%2u|%2u|%2u|%2u|%2u|%2u|%2u|%2u|"
		       "%2u|%2u|%2u|%2u|%2u|%2u|%2u|%2u|\n"
		       "\t\tWeight:%2u|%2u|%2u|%2u|%2u|%2u|%2u|%2u|"
		       "%2u|%2u|%2u|%2u|%2u|%2u|%2u|%2u|\n",
		       e[i + 0].vl, e[i + 1].vl, e[i + 2].vl, e[i + 3].vl,
		       e[i + 4].vl, e[i + 5].vl, e[i + 6].vl, e[i + 7].vl,
		       e[i + 8].vl, e[i + 9].vl, e[i + 10].vl, e[i + 11].vl,
		       e[i + 12].vl, e[i + 13].vl, e[i + 14].vl, e[i + 15].vl,
		       e[i + 0].weight, e[i + 1].weight, e[i + 2].weight,
		       e[i + 3].weight, e[i + 4].weight, e[i + 5].weight,
		       e[i + 6].weight, e[i + 7].weight, e[i + 8].weight,
		       e[i + 9].weight, e[i + 10].weight, e[i + 11].weight,
		       e[i + 12].weight, e[i + 13].weight, e[i + 14].weight,
		       e[i + 15].weight);
}