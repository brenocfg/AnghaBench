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
typedef  union ctl_io {int dummy; } ctl_io ;

/* Variables and functions */
 int /*<<< orphan*/  tpc_done (union ctl_io*) ; 

__attribute__((used)) static void
tpcl_done(union ctl_io *io)
{

	tpc_done(io);
}