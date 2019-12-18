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
 int /*<<< orphan*/  free (char*) ; 
 int kstack_nextstate (int) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  xo_emit (char*,char*) ; 

__attribute__((used)) static void
kstack_cleanup_encoded(const char *old, char *new, int kflag)
{
	enum trace_state old_ts, ts;
	const char *cp_old;
	char *cp_new, *cp_loop, *cp_tofree, *cp_line;

	ts = TS_FRAMENUM;
	if (kflag == 1) {
		for (cp_old = old, cp_new = new; *cp_old != '\0'; cp_old++) {
			switch (*cp_old) {
			case '\n':
				*cp_new = *cp_old;
				cp_new++;
			case ' ':
			case '+':
				old_ts = ts;
				ts = kstack_nextstate(old_ts);
				continue;
			}
			if (ts == TS_FUNC) {
				*cp_new = *cp_old;
				cp_new++;
			}
		}
		*cp_new = '\0';
		cp_tofree = cp_loop = strdup(new);
	} else
		cp_tofree = cp_loop = strdup(old);
        while ((cp_line = strsep(&cp_loop, "\n")) != NULL) {
		if (strlen(cp_line) != 0 && *cp_line != 127)
			xo_emit("{le:token/%s}", cp_line);
	}
	free(cp_tofree);
}