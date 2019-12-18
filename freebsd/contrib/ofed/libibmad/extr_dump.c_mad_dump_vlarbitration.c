#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {TYPE_1__* vl_entry; } ;
typedef  TYPE_2__ ib_vl_arb_table_t ;
struct TYPE_3__ {int weight; int /*<<< orphan*/  res_vl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_vl_arb_get_vl (int /*<<< orphan*/ ,int*) ; 
 int snprintf (char*,int,char*,...) ; 

void mad_dump_vlarbitration(char *buf, int bufsz, void *val, int num)
{
	ib_vl_arb_table_t *p_vla_tbl = val;
	int i, n;
	uint8_t vl;

	num /= sizeof(p_vla_tbl->vl_entry[0]);

	n = snprintf(buf, bufsz, "\nVL    : |");
	if (n >= bufsz)
		return;
	for (i = 0; i < num; i++) {
		ib_vl_arb_get_vl(p_vla_tbl->vl_entry[i].res_vl, &vl);
		n += snprintf(buf + n, bufsz - n, "0x%-2X|", vl);
		if (n >= bufsz)
			return;
	}

	n += snprintf(buf + n, bufsz - n, "\nWEIGHT: |");
	if (n >= bufsz)
		return;
	for (i = 0; i < num; i++) {
		n += snprintf(buf + n, bufsz - n, "0x%-2X|",
			      p_vla_tbl->vl_entry[i].weight);
		if (n >= bufsz)
			return;
	}

	snprintf(buf + n, bufsz - n, "\n");
}