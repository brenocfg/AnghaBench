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
struct fuse_dispatcher {int /*<<< orphan*/  tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  fticket_refresh (int /*<<< orphan*/ ) ; 

void
fdisp_refresh(struct fuse_dispatcher *fdip)
{
	fticket_refresh(fdip->tick);
}