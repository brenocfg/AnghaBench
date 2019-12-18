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
struct t4_wq {int /*<<< orphan*/ * db_offp; } ;

/* Variables and functions */
 int c4iw_abi_version ; 

__attribute__((used)) static inline int t4_wq_db_enabled(struct t4_wq *wq)
{
	/*
	 * If iw_cxgb4 driver supports door bell drop recovery then its
	 * c4iw_abi_version would be greater than or equal to 2. In such
	 * case return the status of db_off flag to ring the kernel mode
	 * DB from user mode library.
	 */
	if ( c4iw_abi_version >= 2 )
		return ! *wq->db_offp;
	else
		return 1;
}