#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/ ** tl_head; int /*<<< orphan*/  tl_spa; } ;
typedef  TYPE_1__ txg_list_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 size_t TXG_MASK ; 
 int /*<<< orphan*/  txg_verify (int /*<<< orphan*/ ,size_t) ; 

boolean_t
txg_list_empty(txg_list_t *tl, uint64_t txg)
{
	txg_verify(tl->tl_spa, txg);
	return (tl->tl_head[txg & TXG_MASK] == NULL);
}