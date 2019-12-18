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
typedef  enum trace_state { ____Placeholder_trace_state } trace_state ;

/* Variables and functions */
 int TS_FRAMENUM ; 
 int TS_FUNC ; 
 int TS_OFF ; 
 int kstack_nextstate (int) ; 

__attribute__((used)) static void
kstack_cleanup(const char *old, char *new, int kflag)
{
	enum trace_state old_ts, ts;
	const char *cp_old;
	char *cp_new;

	ts = TS_FRAMENUM;
	for (cp_old = old, cp_new = new; *cp_old != '\0'; cp_old++) {
		switch (*cp_old) {
		case ' ':
		case '\n':
		case '+':
			old_ts = ts;
			ts = kstack_nextstate(old_ts);
			if (old_ts == TS_OFF) {
				*cp_new = ' ';
				cp_new++;
			}
			if (kflag > 1 && old_ts == TS_FUNC) {
				*cp_new = '+';
				cp_new++;
			}
			continue;
		}
		if (ts == TS_FUNC || (kflag > 1 && ts == TS_OFF)) {
			*cp_new = *cp_old;
			cp_new++;
		}
	}
	*cp_new = '\0';
}