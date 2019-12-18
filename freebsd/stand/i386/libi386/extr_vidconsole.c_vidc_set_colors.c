#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ta_fgcolor; int ta_bgcolor; } ;
typedef  TYPE_1__ teken_attr_t ;
struct env_var {int /*<<< orphan*/  ev_name; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CMD_OK ; 
 int EV_NOHOOK ; 
 int TC_LIGHT ; 
 int TC_WHITE ; 
 scalar_t__ color_name_to_teken (void const*,int*) ; 
 int /*<<< orphan*/  env_setenv (int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strtol (void const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teken ; 
 TYPE_1__* teken_get_defattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_set_defattr (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
vidc_set_colors(struct env_var *ev, int flags, const void *value)
{
	int val = 0;
	char buf[2];
	const void *evalue;
	const teken_attr_t *ap;
	teken_attr_t a;

	if (value == NULL)
		return (CMD_OK);

	if (color_name_to_teken(value, &val)) {
		snprintf(buf, sizeof (buf), "%d", val);
		evalue = buf;
	} else {
		char *end;

		errno = 0;
		val = (int)strtol(value, &end, 0);
		if (errno != 0 || *end != '\0') {
			printf("Allowed values are either ansi color name or "
			    "number from range [0-7].\n");
			return (CMD_OK);
		}
		evalue = value;
	}

	ap = teken_get_defattr(&teken);
	a = *ap;
	if (strcmp(ev->ev_name, "teken.fg_color") == 0) {
		/* is it already set? */
		if (ap->ta_fgcolor == val)
			return (CMD_OK);
		a.ta_fgcolor = val;
	}
	if (strcmp(ev->ev_name, "teken.bg_color") == 0) {
		/* is it already set? */
		if (ap->ta_bgcolor == val)
			return (CMD_OK);
		a.ta_bgcolor = val;
	}

	/* Improve visibility */
	if (a.ta_bgcolor == TC_WHITE)
		a.ta_bgcolor |= TC_LIGHT;

	env_setenv(ev->ev_name, flags | EV_NOHOOK, evalue, NULL, NULL);
	teken_set_defattr(&teken, &a);
	return (CMD_OK);
}