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
struct keymap {char* keym; } ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dir ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  x11 ; 

__attribute__((used)) static void
do_kbdcontrol(struct keymap *km)
{
	char *kbd_cmd;
	asprintf(&kbd_cmd, "kbdcontrol -l %s/%s", dir, km->keym);

	if (!x11)
		system(kbd_cmd);

	fprintf(stderr, "keymap=\"%s\"\n", km->keym);
	free(kbd_cmd);
}