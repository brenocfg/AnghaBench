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
typedef  int /*<<< orphan*/  ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_hw_init_free_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_hw_io_restore_sgl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ocs_hw_io_free_common(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	/* initialize IO fields */
	ocs_hw_init_free_io(io);

	/* Restore default SGL */
	ocs_hw_io_restore_sgl(hw, io);
}