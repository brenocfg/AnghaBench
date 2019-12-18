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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ Wflag ; 
 char* fmt_sockaddr (struct sockaddr*,struct sockaddr*,int) ; 
 scalar_t__ numeric_addr ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 

__attribute__((used)) static int
p_sockaddr(const char *name, struct sockaddr *sa, struct sockaddr *mask,
    int flags, int width)
{
	const char *cp;
	char buf[128];
	int protrusion;

	cp = fmt_sockaddr(sa, mask, flags);

	if (width < 0) {
		snprintf(buf, sizeof(buf), "{:%s/%%s} ", name);
		xo_emit(buf, cp);
		protrusion = 0;
	} else {
		if (Wflag != 0 || numeric_addr) {
			snprintf(buf, sizeof(buf), "{[:%d}{:%s/%%s}{]:} ",
			    -width, name);
			xo_emit(buf, cp);
			protrusion = strlen(cp) - width;
			if (protrusion < 0)
				protrusion = 0;
		} else {
			snprintf(buf, sizeof(buf), "{[:%d}{:%s/%%-.*s}{]:} ",
			    -width, name);
			xo_emit(buf, width, cp);
			protrusion = 0;
		}
	}
	return (protrusion);
}