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
struct padinfo {int tmr_num; int /*<<< orphan*/ * ballname; } ;
typedef  int /*<<< orphan*/  muxmode ;

/* Variables and functions */
 unsigned int RXACTIVE ; 
 struct padinfo* dmtpps_padinfo ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int ti_pinmux_padconf_get (int /*<<< orphan*/ *,char const**,unsigned int*) ; 

__attribute__((used)) static int
dmtpps_find_tmr_num_by_padconf(void)
{
	int err;
	unsigned int padstate;
	const char * padmux;
	struct padinfo *pi;
	char muxmode[12];

	for (pi = dmtpps_padinfo; pi->ballname != NULL; pi++) {
		err = ti_pinmux_padconf_get(pi->ballname, &padmux, &padstate);
		snprintf(muxmode, sizeof(muxmode), "timer%d", pi->tmr_num);
		if (err == 0 && (padstate & RXACTIVE) != 0 &&
		    strcmp(muxmode, padmux) == 0)
			return (pi->tmr_num);
	}
	/* Nothing found, not an error. */
	return (0);
}