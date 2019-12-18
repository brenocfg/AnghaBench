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
struct cudbg_init {int dummy; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {int dummy; } ;

/* Variables and functions */
 int read_cim_ibq (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_error*,int) ; 

__attribute__((used)) static int collect_cim_ibq_tp0(struct cudbg_init *pdbg_init,
			       struct cudbg_buffer *dbg_buff,
			       struct cudbg_error *cudbg_err)
{
	int rc = 0, qid = 0;

	rc = read_cim_ibq(pdbg_init, dbg_buff, cudbg_err, qid);
	return rc;
}