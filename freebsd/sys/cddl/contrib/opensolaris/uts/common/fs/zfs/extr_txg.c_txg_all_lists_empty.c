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
typedef  int /*<<< orphan*/  txg_list_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int TXG_SIZE ; 
 int /*<<< orphan*/  txg_list_empty (int /*<<< orphan*/ *,int) ; 

boolean_t
txg_all_lists_empty(txg_list_t *tl)
{
	for (int i = 0; i < TXG_SIZE; i++) {
		if (!txg_list_empty(tl, i)) {
			return (B_FALSE);
		}
	}
	return (B_TRUE);
}