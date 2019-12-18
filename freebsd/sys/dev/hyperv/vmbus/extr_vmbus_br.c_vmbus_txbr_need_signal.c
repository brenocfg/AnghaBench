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
typedef  scalar_t__ uint32_t ;
struct vmbus_txbr {scalar_t__ txbr_rindex; scalar_t__ txbr_imask; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __compiler_membar () ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static __inline boolean_t
vmbus_txbr_need_signal(const struct vmbus_txbr *tbr, uint32_t old_windex)
{
	mb();
	if (tbr->txbr_imask)
		return (FALSE);

	__compiler_membar();

	/*
	 * This is the only case we need to signal when the
	 * ring transitions from being empty to non-empty.
	 */
	if (old_windex == tbr->txbr_rindex)
		return (TRUE);

	return (FALSE);
}