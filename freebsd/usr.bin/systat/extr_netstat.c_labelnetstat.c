#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ n_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FADDR ; 
 int /*<<< orphan*/  LADDR ; 
 int /*<<< orphan*/  PROTO ; 
 int /*<<< orphan*/  RCVCC ; 
 int /*<<< orphan*/  SNDCC ; 
 int /*<<< orphan*/  STATE ; 
 size_t X_TCB ; 
 int /*<<< orphan*/  mvwaddstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* namelist ; 
 scalar_t__ use_kvm ; 
 int /*<<< orphan*/  wclrtobot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnd ; 

void
labelnetstat(void)
{
	if (use_kvm && namelist[X_TCB].n_type == 0)
		return;
	wmove(wnd, 0, 0); wclrtobot(wnd);
	mvwaddstr(wnd, 0, LADDR, "Local Address");
	mvwaddstr(wnd, 0, FADDR, "Foreign Address");
	mvwaddstr(wnd, 0, PROTO, "Proto");
	mvwaddstr(wnd, 0, RCVCC, "Recv-Q");
	mvwaddstr(wnd, 0, SNDCC, "Send-Q");
	mvwaddstr(wnd, 0, STATE, "(state)");
}