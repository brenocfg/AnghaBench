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
struct fuse_dispatcher {size_t iosize; int /*<<< orphan*/ * tick; } ;

/* Variables and functions */

__attribute__((used)) static inline void
fdisp_init(struct fuse_dispatcher *fdisp, size_t iosize)
{
	fdisp->iosize = iosize;
	fdisp->tick = NULL;
}