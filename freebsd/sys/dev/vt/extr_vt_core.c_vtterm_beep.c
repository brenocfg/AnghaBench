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
typedef  int u_int ;
struct terminal {int dummy; } ;

/* Variables and functions */
 int hz ; 
 int /*<<< orphan*/  sysbeep (int,int) ; 
 int /*<<< orphan*/  vt_enable_bell ; 
 int /*<<< orphan*/  vtterm_bell (struct terminal*) ; 

__attribute__((used)) static void
vtterm_beep(struct terminal *tm, u_int param)
{
	u_int freq, period;

	if (!vt_enable_bell)
		return;

	if ((param == 0) || ((param & 0xffff) == 0)) {
		vtterm_bell(tm);
		return;
	}

	period = ((param >> 16) & 0xffff) * hz / 1000;
	freq = 1193182 / (param & 0xffff);

	sysbeep(freq, period);
}