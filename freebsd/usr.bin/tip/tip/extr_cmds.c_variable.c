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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int v_access; } ;

/* Variables and functions */
 size_t BEAUTIFY ; 
 int CHANGED ; 
 size_t HARDWAREFLOW ; 
 scalar_t__ HD ; 
 size_t LECHO ; 
 size_t LINEDISC ; 
 int /*<<< orphan*/  NOSTR ; 
 size_t PARITY ; 
 size_t RECORD ; 
 size_t SCRIPT ; 
 int /*<<< orphan*/  SIGSYS ; 
 size_t TAND ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hardwareflow (char*) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linedisc (int /*<<< orphan*/ ) ; 
 scalar_t__ prompt (char*,char*,int) ; 
 int /*<<< orphan*/  setparity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setscript () ; 
 int /*<<< orphan*/  tandem (char*) ; 
 int /*<<< orphan*/  tipout_pid ; 
 int /*<<< orphan*/  value (size_t) ; 
 int /*<<< orphan*/  vlex (char*) ; 
 TYPE_1__* vtable ; 

void
variable(int c)
{
	char	buf[256];

	if (prompt("[set] ", buf, sizeof(buf)))
		return;
	vlex(buf);
	if (vtable[BEAUTIFY].v_access&CHANGED) {
		vtable[BEAUTIFY].v_access &= ~CHANGED;
		kill(tipout_pid, SIGSYS);
	}
	if (vtable[SCRIPT].v_access&CHANGED) {
		vtable[SCRIPT].v_access &= ~CHANGED;
		setscript();
		/*
		 * So that "set record=blah script" doesn't
		 *  cause two transactions to occur.
		 */
		if (vtable[RECORD].v_access&CHANGED)
			vtable[RECORD].v_access &= ~CHANGED;
	}
	if (vtable[RECORD].v_access&CHANGED) {
		vtable[RECORD].v_access &= ~CHANGED;
		if (boolean(value(SCRIPT)))
			setscript();
	}
	if (vtable[TAND].v_access&CHANGED) {
		vtable[TAND].v_access &= ~CHANGED;
		if (boolean(value(TAND)))
			tandem("on");
		else
			tandem("off");
	}
	if (vtable[LECHO].v_access&CHANGED) {
		vtable[LECHO].v_access &= ~CHANGED;
		HD = boolean(value(LECHO));
	}
	if (vtable[PARITY].v_access&CHANGED) {
		vtable[PARITY].v_access &= ~CHANGED;
		setparity(NOSTR);
	}
	if (vtable[HARDWAREFLOW].v_access&CHANGED) {
		vtable[HARDWAREFLOW].v_access &= ~CHANGED;
		if (boolean(value(HARDWAREFLOW)))
			hardwareflow("on");
		else
			hardwareflow("off");
	}
	if (vtable[LINEDISC].v_access&CHANGED) {
		vtable[LINEDISC].v_access &= ~CHANGED;
		linedisc(NOSTR);
	}
}