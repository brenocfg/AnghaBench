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
typedef  int /*<<< orphan*/  uint32_t ;
struct octeon_device {int dummy; } ;
struct lio_soft_command {scalar_t__ ctxptr; } ;
struct lio_ctrl_pkt {int /*<<< orphan*/  (* cb_fn ) (struct lio_ctrl_pkt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lio_free_soft_command (struct octeon_device*,struct lio_soft_command*) ; 
 int /*<<< orphan*/  stub1 (struct lio_ctrl_pkt*) ; 

__attribute__((used)) static void
lio_ctrl_callback(struct octeon_device *oct, uint32_t status, void *sc_ptr)
{
	struct lio_soft_command	*sc = (struct lio_soft_command *)sc_ptr;
	struct lio_ctrl_pkt	*nctrl;

	nctrl = (struct lio_ctrl_pkt *)sc->ctxptr;

	/*
	 * Call the callback function if status is OK.
	 * Status is OK only if a response was expected and core returned
	 * success.
	 * If no response was expected, status is OK if the command was posted
	 * successfully.
	 */
	if (!status && nctrl->cb_fn)
		nctrl->cb_fn(nctrl);

	lio_free_soft_command(oct, sc);
}