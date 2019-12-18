#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int keynum; int /*<<< orphan*/  keydef; int /*<<< orphan*/  flen; } ;
typedef  TYPE_1__ fkeyarg_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAXFK ; 
 int NUM_FKEYS ; 
 int /*<<< orphan*/  SETFKEY ; 
 int atoi (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  load_default_functionkeys () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,int,...) ; 

__attribute__((used)) static void
set_functionkey(char *keynumstr, char *string)
{
	fkeyarg_t fkey;

	if (!strcmp(keynumstr, "load") && !strcmp(string, "default")) {
		load_default_functionkeys();
		return;
	}
	fkey.keynum = atoi(keynumstr);
	if (fkey.keynum < 1 || fkey.keynum > NUM_FKEYS) {
		warnx("function key number must be between 1 and %d",
			NUM_FKEYS);
		return;
	}
	if ((fkey.flen = strlen(string)) > MAXFK) {
		warnx("function key string too long (%d > %d)",
			fkey.flen, MAXFK);
		return;
	}
	strncpy(fkey.keydef, string, MAXFK);
	fkey.keynum -= 1;
	if (ioctl(0, SETFKEY, &fkey) < 0)
		warn("setting function key");
}