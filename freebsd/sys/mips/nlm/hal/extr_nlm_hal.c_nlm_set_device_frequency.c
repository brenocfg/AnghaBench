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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_DFS_DIV_DEC_CTRL ; 
 int /*<<< orphan*/  SYS_DFS_DIV_INC_CTRL ; 
 int nlm_get_device_frequency (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_get_sys_regbase (int) ; 
 int /*<<< orphan*/  nlm_write_sys_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
nlm_set_device_frequency(int node, int devtype, int frequency)
{
	uint64_t sysbase;
	u_int cur_freq;
	int dec_div;

	sysbase = nlm_get_sys_regbase(node);
	cur_freq = nlm_get_device_frequency(sysbase, devtype);
	if (cur_freq < (frequency - 5))
		dec_div = 1;
	else
		dec_div = 0;

	for(;;) {
		if ((cur_freq >= (frequency - 5)) && (cur_freq <= frequency))
			break;
		if (dec_div)
			nlm_write_sys_reg(sysbase, SYS_DFS_DIV_DEC_CTRL,
			    (1 << devtype));
		else
			nlm_write_sys_reg(sysbase, SYS_DFS_DIV_INC_CTRL,
			    (1 << devtype));
		cur_freq = nlm_get_device_frequency(sysbase, devtype);
	}
	return (nlm_get_device_frequency(sysbase, devtype));
}