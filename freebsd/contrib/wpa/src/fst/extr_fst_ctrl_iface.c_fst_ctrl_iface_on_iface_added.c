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
struct fst_iface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fst_ctrl_iface_on_iface_state_changed (struct fst_iface*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fst_ctrl_iface_on_iface_added(struct fst_iface *i)
{
	fst_ctrl_iface_on_iface_state_changed(i, TRUE);
	return 0;
}