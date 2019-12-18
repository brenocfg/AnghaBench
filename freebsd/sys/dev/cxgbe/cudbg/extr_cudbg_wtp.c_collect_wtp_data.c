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
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_t5 (struct adapter*) ; 
 scalar_t__ is_t6 (struct adapter*) ; 
 int t5_wtp_data (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_error*) ; 
 int t6_wtp_data (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_error*) ; 

int collect_wtp_data(struct cudbg_init *pdbg_init,
		     struct cudbg_buffer *dbg_buff,
		     struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	int rc = -1;

	if (is_t5(padap))
		rc = t5_wtp_data(pdbg_init, dbg_buff, cudbg_err);
	else if (is_t6(padap))
		rc = t6_wtp_data(pdbg_init, dbg_buff, cudbg_err);

	return rc;
}