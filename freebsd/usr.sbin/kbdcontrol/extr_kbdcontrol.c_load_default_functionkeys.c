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
struct TYPE_3__ {int keynum; int /*<<< orphan*/  flen; int /*<<< orphan*/  keydef; } ;
typedef  TYPE_1__ fkeyarg_t ;

/* Variables and functions */
 int NUM_FKEYS ; 
 int /*<<< orphan*/  SETFKEY ; 
 int /*<<< orphan*/ * fkey_table ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
load_default_functionkeys(void)
{
	fkeyarg_t fkey;
	int i;

	for (i=0; i<NUM_FKEYS; i++) {
		fkey.keynum = i;
		strcpy(fkey.keydef, fkey_table[i]);
		fkey.flen = strlen(fkey_table[i]);
		if (ioctl(0, SETFKEY, &fkey) < 0)
			warn("setting function key");
	}
}