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
struct fuse_ticket {int /*<<< orphan*/  tk_aw_mtx; int /*<<< orphan*/  tk_aw_fiov; int /*<<< orphan*/  tk_ms_fiov; } ;

/* Variables and functions */
 int /*<<< orphan*/  fiov_teardown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fticket_fini(void *mem, int size)
{
	struct fuse_ticket *ftick = mem;

	fiov_teardown(&ftick->tk_ms_fiov);
	fiov_teardown(&ftick->tk_aw_fiov);
	mtx_destroy(&ftick->tk_aw_mtx);
}