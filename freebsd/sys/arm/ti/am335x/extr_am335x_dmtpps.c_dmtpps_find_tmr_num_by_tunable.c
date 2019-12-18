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
typedef  int /*<<< orphan*/  iname ;

/* Variables and functions */
 int /*<<< orphan*/  PADCONF_INPUT ; 
 int /*<<< orphan*/  TUNABLE_STR_FETCH (char*,char*,int) ; 
 scalar_t__ bootverbose ; 
 struct padinfo* dmtpps_padinfo ; 
 char* dmtpps_translate_nickname (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 int ti_pinmux_padconf_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmtpps_find_tmr_num_by_tunable(void)
{
	struct padinfo *pi;
	char iname[20];
	char muxmode[12];
	const char * ballname;
	int err;

	if (!TUNABLE_STR_FETCH("hw.am335x_dmtpps.input", iname, sizeof(iname)))
		return (0);
	ballname = dmtpps_translate_nickname(iname);
	for (pi = dmtpps_padinfo; pi->ballname != NULL; pi++) {
		if (strcmp(ballname, pi->ballname) != 0)
			continue;
		snprintf(muxmode, sizeof(muxmode), "timer%d", pi->tmr_num);
		err = ti_pinmux_padconf_set(pi->ballname, muxmode,
		    PADCONF_INPUT);
		if (err != 0) {
			printf("am335x_dmtpps: unable to configure capture pin "
			    "for %s to input mode\n", muxmode);
			return (-1);
		} else if (bootverbose) {
			printf("am335x_dmtpps: configured pin %s as input "
			    "for %s\n", iname, muxmode);
		}
		return (pi->tmr_num);
	}

	/* Invalid name in the tunable, that's an error. */
	printf("am335x_dmtpps: unknown pin name '%s'\n", iname);
	return (-1);
}