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
struct ctl_table {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {int /*<<< orphan*/  prid; } ;
struct TYPE_4__ {int /*<<< orphan*/  li_prid; TYPE_1__ li_eeprom_info; } ;

/* Variables and functions */
 TYPE_2__ lasat_board_info ; 
 int /*<<< orphan*/  lasat_init_board_info () ; 
 int /*<<< orphan*/  lasat_write_eeprom_info () ; 
 int proc_dointvec (struct ctl_table*,int,void*,size_t*,int /*<<< orphan*/ *) ; 

int proc_lasat_prid(struct ctl_table *table, int write,
		       void *buffer, size_t *lenp, loff_t *ppos)
{
	int r;

	r = proc_dointvec(table, write, buffer, lenp, ppos);
	if (r < 0)
		return r;
	if (write) {
		lasat_board_info.li_eeprom_info.prid =
			lasat_board_info.li_prid;
		lasat_write_eeprom_info();
		lasat_init_board_info();
	}
	return 0;
}