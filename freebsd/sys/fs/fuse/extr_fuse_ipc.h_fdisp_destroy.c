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
struct fuse_dispatcher {int /*<<< orphan*/ * tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_ticket_drop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
fdisp_destroy(struct fuse_dispatcher *fdisp)
{
	fuse_ticket_drop(fdisp->tick);
#ifdef INVARIANTS
	fdisp->tick = NULL;
#endif
}